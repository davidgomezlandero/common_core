# 🔐 Secrets - Centralized Management of Sensitive Information

## 📋 General Overview

This directory is the centralized repository of **all sensitive information** in the project: credentials, tokens, SSL certificates and security configurations. It implements the "secrets separation" principle from source code for maximum security.

## 🗂️ Subdirectory Structure

### 📁 `api-approle/`
**Purpose**: AppRole authentication credentials for HashiCorp Vault.

**Contains**:
- `role_id`: Application role identifier
- `secret_id`: Secret credential (equivalent to a password)

**Usage**: Backend authenticates with Vault using these credentials to access dynamic secrets.

**Documentation**: See [api-approle/README.md](./api-approle/README.md)

---

### 🔒 `certs/`
**Purpose**: SSL/TLS certificates for HTTPS communications.

**Contains**:
- `fullchain.pem`: Full certificate chain
- `privkey.pem`: Server private key
- `cert.conf`: OpenSSL configuration for generation

**Usage**: Nginx and web services to enable secure HTTPS.

**Documentation**: See [certs/README.md](./certs/README.md)

---

### 🗝️ `vault/`
**Purpose**: Vault master initialization keys.

**Contains**:
- `init.txt`: Full output of `vault operator init`
- `unseal_key`: One of the unseal keys
- `root_token`: Supreme administrative token

**Usage**: Vault initialization and unsealing after restarts.

**Documentation**: See [vault/README.md](./vault/README.md)

---

### 📄 `.env`
**Purpose**: Sensitive environment variables loaded by the backend.

**Contains**:
```env
# Database
DATABASE_URL=sqlite:./database.sqlite

# JWT
JWT_SECRET=supersecretkey_change_in_production

# OAuth (if enabled)
GOOGLE_CLIENT_ID=your_google_client_id
GOOGLE_CLIENT_SECRET=your_google_client_secret

# Vault (if enabled)
VAULT_ADDR=http://vault:8200
VAULT_TOKEN=hvs.CAESID...
```

**Loading**: Backend uses `dotenv` to read on startup.

---

### 🗄️ `app.db`
**Purpose**: SQLite database with user information (development).

**Contains**:
- `Users` table: hashed credentials, profiles
- `Friendships` table: relationships between users
- `Matches` table: match history
- `Conversations` and `Messages` tables: chat
- `BlockedUsers` table: blocked users

**Production**: Migrate to PostgreSQL or MySQL.

---

## 🔄 Secrets Access Flow

```
1. Secrets at rest (this directory)
   ↓
2. Docker Compose mounts volumes:
   - ./srcs/secrets:/app/secrets:ro (backend)
   - ./srcs/secrets/certs:/etc/ssl/certs:ro (nginx)
   ↓
3. Applications read secrets:
   - Backend: process.env (from .env)
   - Backend: fs.readFileSync('/app/secrets/...')
   - Nginx: ssl_certificate directives
   ↓
4. Authentication with external services:
   - Vault: AppRole login
   - Database: connection string
   - OAuth: client credentials
```

## 🛡️ Multi-Level Security

### Level 1: Filesystem Protection
```bash
# Restrictive permissions
chmod 700 srcs/secrets/
chmod 600 srcs/secrets/*/.
chmod 600 srcs/secrets/**/*

# Specific owner
chown -R $(whoami):$(whoami) srcs/secrets/
```

### Level 2: Git Exclusion
```gitignore
# .gitignore
srcs/secrets/.env
srcs/secrets/**/*.pem
srcs/secrets/**/secret_id
srcs/secrets/**/root_token
srcs/secrets/**/unseal_key
srcs/secrets/app.db
```

### Level 3: Docker Read-Only Mounts
```yaml
volumes:
  - ./srcs/secrets:/app/secrets:ro  # ← :ro = read-only
```

### Level 4: Vault Dynamic Secrets
Instead of static secrets, use Vault for:
- Temporary DB credentials (TTL 1h)
- Rotating API keys
- Dynamically generated certificates

## 🔗 Project Integration

### Backend (`backend/pon-server.js`)
```javascript
import 'dotenv/config';  // Reads .env automatically
import fs from 'fs';

// Access secrets
const jwtSecret = process.env.JWT_SECRET;
const vaultToken = fs.readFileSync('/app/secrets/vault/root_token', 'utf8');
```

### Docker Compose (`docker-compose.yml`)
```yaml
services:
  backend:
    environment:
      - NODE_ENV=production
      - JWT_SECRET=${JWT_SECRET}  # From host .env
    volumes:
      - ./srcs/secrets:/app/secrets:ro
```

### Nginx (`srcs/conf/nginx/nginx.conf`)
```nginx
ssl_certificate /etc/ssl/certs/fullchain.pem;
ssl_certificate_key /etc/ssl/certs/privkey.pem;
```

## 🔄 Secrets Management by Environment

### Development
- Auto-generated secrets (`00.gen_selfsigned_cert.sh`)
- `.env` with dummy values is OK
- SQLite in local file
- Vault in dev mode (no persistence)

### Staging
- Semi-real secrets (valid certificates for `staging.domain.com`)
- `.env` with staging values
- PostgreSQL in Docker container
- Persistent Vault with backups

### Production
- Secrets from external CA (Let's Encrypt)
- `.env` injected from CI/CD (GitHub Secrets, AWS Secrets Manager)
- Managed PostgreSQL/MySQL (RDS, Cloud SQL)
- Vault in HA cluster with distributed unseal keys

## 🧪 Full Initialization

```bash
# 1. Generate SSL certificates
./srcs/scripts/00.gen_selfsigned_cert.sh

# 2. Create base .env
cp srcs/secrets/.env.example srcs/secrets/.env
nano srcs/secrets/.env  # Edit values

# 3. Initialize Vault (if used)
docker-compose up -d vault
./srcs/scripts/01.init_waf_and_vault.sh

# 4. Verify access
./srcs/scripts/02.read_vault_from_host.sh

# 5. Start full stack
docker-compose up -d

# 6. Verify secrets access
docker exec transcendence-backend ls -la /app/secrets
```

## 📊 Secrets Inventory

| File/Directory | Type | Sensitivity | Rotation | Backup |
|----------------|------|-------------|----------|--------|
| `api-approle/secret_id` | Credential | 🔴 Critical | 30 days | No (regenerable) |
| `certs/privkey.pem` | Private Key | 🔴 Critical | 90 days | Yes (offline) |
| `vault/root_token` | Token | 🔴 Maximum | Post-setup | Yes (encrypted) |
| `vault/unseal_key` | Key | 🔴 Maximum | 90 days | Yes (distributed) |
| `.env` | Config | 🟡 Medium | Version change | Yes (versioned) |
| `app.db` | Database | 🟢 Low (dev) | N/A | Optional |

## 🚨 Compromise Procedure

If secrets exposure is suspected:

### Immediate Action
```bash
# 1. Revoke all Vault tokens
docker exec vault vault token revoke -mode=path auth/approle

# 2. Regenerate secret_id
docker exec vault vault write -f -field=secret_id auth/approle/role/myapp/secret-id > api-approle/secret_id

# 3. Regenerate SSL certificates
./srcs/scripts/00.gen_selfsigned_cert.sh

# 4. Change JWT_SECRET in .env
openssl rand -base64 32 > .jwt_secret_new

# 5. Restart all services
docker-compose down
docker-compose up -d

# 6. Invalidate user sessions
docker exec transcendence-backend node -e "
const db = require('./db.js');
db.User.update({ sessionVersion: 0 }, { where: {} });
"
```

### Post-Incident
- Full log audit
- Forced user password rotation
- Review of unauthorized accesses
- Incident documentation update

## 📚 References and Best Practices

### Internal Documents
- [api-approle/README.md](./api-approle/README.md) - AppRole authentication
- [certs/README.md](./certs/README.md) - TLS/SSL certificates
- [vault/README.md](./vault/README.md) - Vault initialization keys

### External Resources
- [12-Factor App: Config](https://12factor.net/config)
- [OWASP Secrets Management](https://cheatsheetseries.owasp.org/cheatsheets/Secrets_Management_Cheat_Sheet.html)
- [HashiCorp Vault Best Practices](https://learn.hashicorp.com/tutorials/vault/pattern-approle)
- [Mozilla Web Security Guidelines](https://infosec.mozilla.org/guidelines/web_security)

### Related Scripts
- `../scripts/00.gen_selfsigned_cert.sh` - Certificate generation
- `../scripts/01.init_waf_and_vault.sh` - Vault initialization
- `../scripts/02.read_vault_from_host.sh` - Access verification
- `../scripts/03.test_vault_secrets_from_container.sh` - Integration tests

---

**Location**: `/srcs/secrets/`  
**Owner**: DevOps / Security Team  
**Access level**: Restricted (senior developers and CI/CD only)  
**Audit**: Access logs enabled in Vault and filesystem