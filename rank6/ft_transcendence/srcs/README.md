# 📂 SRCS - Project Infrastructure and Configuration

## 📋 General Overview

This directory contains all the **support infrastructure** for the Transcendence project. It includes service configurations (Nginx, ModSecurity WAF, Vault), automation scripts, application logs, persistent data and secrets management.

## 🗂️ Main Structure

```
srcs/
├── conf/                  # Service configurations
│   ├── nginx/            # Reverse proxy and load balancer
│   └── modsecurity/      # Web Application Firewall
│       ├── custom-rules/ # Custom WAF rules (18 files)
│       ├── custom-rules-options/
│       └── owasp-crs/    # Complete OWASP Core Rule Set
│
├── secrets/              # Secrets and credentials management
│   ├── api-approle/     # Vault AppRole (role_id, secret_id)
│   ├── certs/           # SSL/TLS certificates
│   ├── vault/           # Vault initialization keys
│   ├── .env             # Environment variables
│   └── app.db           # SQLite database
│
├── data/                 # Persistent data
│   └── vault/
│       ├── config/      # Vault configuration
│       └── file/        # Vault storage backend
│
├── logs/                 # Application logs
│   ├── nginx/           # Nginx access and error logs
│   └── modsec/          # ModSecurity audit logs
│
└── scripts/              # Automation scripts
    ├── 00.gen_selfsigned_cert.sh       # Generate SSL certificates
    ├── 01.init_waf_and_vault.sh        # Full initialization
    ├── 02.read_vault_from_host.sh      # Read Vault secrets
    ├── 03.test_vault_secrets_from_container.sh
    └── 99.test_modsec_rules.sh         # WAF rules testing
```

## 🛡️ Security Components

### 1. **Nginx** (`conf/nginx/`)

**Function**: Reverse proxy, load balancer, SSL/TLS termination.

**Features**:
- Request routing (`/api` → backend, `/` → frontend)
- Gzip compression
- Static asset caching
- Per-endpoint rate limiting
- HTTP security headers
- HTTP/2 support

**Main configuration**: `nginx.conf`

**Documentation**: [conf/nginx/README.md](./conf/nginx/README.md) (if exists)

---

### 2. **ModSecurity WAF** (`conf/modsecurity/`)

**Function**: Web Application Firewall to detect and block web attacks.

**Protections**:
- **XSS** (Cross-Site Scripting)
- **SQLi** (SQL Injection)
- **LFI/RFI** (Local/Remote File Inclusion)
- **CSRF** (Cross-Site Request Forgery)
- **Command Injection**
- **Malicious User-Agents**

**Rules**:
- **OWASP CRS**: 3000+ community rules
- **Custom Rules**: 18+ rules specific to Transcendence

**Modes**:
- **Detection Only**: Logs but does not block (development)
- **Blocking**: Blocks malicious requests (production)

**Full documentation**: [conf/modsecurity/README.md](./conf/modsecurity/README.md)

---

### 3. **HashiCorp Vault** (`secrets/vault/`, `data/vault/`)

**Function**: Centralized secrets management (passwords, API keys, tokens).

**Features**:
- **Encryption at rest**: AES-256-GCM
- **Unsealing**: Requires 3 of 5 keys (Shamir's Secret Sharing)
- **AppRole Auth**: Authentication for backend services
- **Secret Rotation**: Automatic secret renewal
- **Audit Logging**: Complete access logging

**Stored secrets**:
- JWT secrets (access + refresh tokens)
- Database credentials
- OAuth client secrets (Google, 42)
- Third-party API keys

**Documentation**: [secrets/vault/README.md](./secrets/vault/README.md)

---

## 🔐 Secrets Management (`secrets/`)

### Sensitive Files

| File | Description | Example |
|------|-------------|---------|
| `api-approle/role_id` | Vault AppRole role ID | `abc123...` |
| `api-approle/secret_id` | Secret ID for authentication | `xyz789...` |
| `certs/fullchain.pem` | Public SSL certificate | `-----BEGIN CERTIFICATE-----` |
| `certs/privkey.pem` | SSL private key | `-----BEGIN PRIVATE KEY-----` |
| `vault/init.txt` | Full output of `vault operator init` | Unseal Keys + Root Token |
| `vault/unseal_key` | First extracted unseal key | `Unseal Key 1: ...` |
| `vault/root_token` | Vault root token | `hvs.CAESIAbcDef...` |
| `.env` | Environment variables | `JWT_SECRET=...` |
| `app.db` | SQLite database | Binary |

### Security Levels

```
1. Filesystem Permissions
   → chmod 600 secrets/*
   → Only root/owner can read

2. Git Ignore
   → secrets/ in .gitignore
   → Never commit

3. Docker Secrets
   → Secure mounting in containers
   → Not in environment variables

4. Vault Encryption
   → Secrets encrypted in Vault
   → Decrypted only when in use
```

---

## 📊 Logging (`logs/`)

### Nginx Logs (`logs/nginx/`)

```
access.log         → All HTTP requests
error.log          → Nginx errors
access_modsec.log  → Requests with ModSecurity info
```

**access.log format**:
```
127.0.0.1 - - [01/Jan/2024:12:00:00 +0000] "GET /api/users/1 HTTP/1.1" 200 1234 "-" "Mozilla/5.0"
```

### ModSecurity Logs (`logs/modsec/`)

```
modsec_audit.log   → Blocked/detected requests
modsec_debug.log   → Detailed debug (only with SecDebugLogLevel > 0)
```

**audit.log format** (JSON):
```json
{
  "transaction": {
    "client_ip": "192.168.1.100",
    "time": "01/Jan/2024:12:00:00 +0000",
    "request": {
      "method": "GET",
      "uri": "/api/users?search=<script>alert(1)</script>",
      "headers": {...}
    },
    "response": {
      "http_code": 403
    },
    "messages": [
      {
        "message": "XSS Attack Detected",
        "ruleId": "941100",
        "severity": "CRITICAL"
      }
    ]
  }
}
```

### Log Monitoring

```bash
# Real-time tail
tail -f srcs/logs/nginx/access.log
tail -f srcs/logs/modsec/modsec_audit.log

# Search for XSS attacks
grep "941100" srcs/logs/modsec/modsec_audit.log

# Count requests per IP
awk '{print $1}' srcs/logs/nginx/access.log | sort | uniq -c | sort -nr

# View top 10 most accessed endpoints
awk '{print $7}' srcs/logs/nginx/access.log | sort | uniq -c | sort -nr | head -10
```

---

## 💾 Persistent Data (`data/`)

### Vault Data (`data/vault/`)

```
config/         → vault.hcl (server configuration)
file/           → Storage backend (encrypted files)
```

**Vault Backup**:
```bash
# Data backup
tar -czf vault-backup-$(date +%Y%m%d).tar.gz srcs/data/vault/

# Keys backup
tar -czf vault-keys-$(date +%Y%m%d).tar.gz srcs/secrets/vault/

# Restore
tar -xzf vault-backup-20240101.tar.gz -C srcs/data/
```

---

## 🚀 Automation Scripts (`scripts/`)

### Full Initialization

```bash
# 1. Generate self-signed SSL certificates
./srcs/scripts/00.gen_selfsigned_cert.sh

# 2. Initialize WAF, Vault, AppRole, logs
./srcs/scripts/01.init_waf_and_vault.sh

# 3. Verify Vault access from host
./srcs/scripts/02.read_vault_from_host.sh

# 4. Test Vault from container
./srcs/scripts/03.test_vault_secrets_from_container.sh

# 5. Test ModSecurity rules
./srcs/scripts/99.test_modsec_rules.sh
```

**Full documentation**: [scripts/README.md](./scripts/README.md)

---

## 🔗 Docker Compose Integration

```yaml
# docker-compose.yml (simplified example)
services:
  vault:
    image: hashicorp/vault:1.15
    volumes:
      - ./srcs/data/vault/file:/vault/file
      - ./srcs/data/vault/config:/vault/config
    environment:
      VAULT_ADDR: http://0.0.0.0:8200
    cap_add:
      - IPC_LOCK

  nginx:
    image: nginx:alpine
    volumes:
      - ./srcs/conf/nginx/nginx.conf:/etc/nginx/nginx.conf:ro
      - ./srcs/secrets/certs:/etc/nginx/certs:ro
      - ./srcs/logs/nginx:/var/log/nginx
      - ./srcs/conf/modsecurity:/etc/nginx/modsec:ro
      - ./srcs/logs/modsec:/var/log/modsec
    ports:
      - "443:443"
      - "80:80"
```

---

## 🧪 Security Testing

### Validate Configurations

```bash
# Nginx syntax test
docker-compose exec nginx nginx -t

# Nginx reload without downtime
docker-compose exec nginx nginx -s reload

# Verify loaded ModSecurity rules
docker-compose exec nginx grep -r "SecRule" /etc/nginx/modsec/

# View Vault status
docker-compose exec vault vault status
```

### Penetration Testing

```bash
# XSS Attack (should be blocked: 403)
curl -k "https://localhost/api/users?search=<script>alert(1)</script>"

# SQLi Attack (should be blocked: 403)
curl -k "https://localhost/api/users?id=1' OR '1'='1"

# LFI Attack (should be blocked: 403)
curl -k "https://localhost/api/files?path=../../../../etc/passwd"

# Rate Limiting Test
for i in {1..10}; do
  curl -X POST https://localhost/api/auth/login \
    -H "Content-Type: application/json" \
    -d '{"username":"test","password":"test"}'
done
# 6th request should fail with 429 Too Many Requests
```

### Automated Testing

```bash
# Run complete WAF test suite
./srcs/scripts/99.test_modsec_rules.sh

# Expected output:
# Testing XSS in query param... ✅ PASS (got 403)
# Testing SQLi UNION attack... ✅ PASS (got 403)
# Testing LFI attempt... ✅ PASS (got 403)
# Testing Valid API request... ✅ PASS (200)
# Testing Login rate limit (6th request)... ✅ PASS (429)
# ==============================
# Tests Passed: 5
# Tests Failed: 0
# ==============================
```

---

## 📈 Monitoring and Alerts

### Nginx Metrics

```bash
# Enable stub_status in nginx.conf
curl http://localhost/nginx_status

# Output:
# Active connections: 42
# server accepts handled requests
#  1234 1234 5678
# Reading: 0 Writing: 5 Waiting: 37
```

### Attack Alerts

```bash
# Real-time monitoring script
tail -f srcs/logs/modsec/modsec_audit.log | \
grep -E "id \"(942100|941100|930100)\"" | \
while read line; do
  echo "🚨 ALERT: Attack detected - $line"
  # Send notification (email, Slack, etc.)
done
```

---

## 🔧 Maintenance

### Log Rotation

```bash
# logrotate.conf
/path/to/srcs/logs/nginx/*.log {
    daily
    rotate 14
    compress
    delaycompress
    notifempty
    missingok
    sharedscripts
    postrotate
        docker-compose exec nginx nginx -s reload
    endscript
}
```

### Certificate Renewal

```bash
# Self-signed certificates: regenerate every 365 days
rm srcs/secrets/certs/{fullchain,privkey}.pem
./srcs/scripts/00.gen_selfsigned_cert.sh

# Let's Encrypt (production):
certbot renew --webroot -w /var/www/html
# Copy new certificates to srcs/secrets/certs/
```

### Automatic Backup

```bash
# Daily cronjob
0 2 * * * tar -czf /backups/srcs-$(date +\%Y\%m\%d).tar.gz \
  /path/to/transcendence/srcs/secrets \
  /path/to/transcendence/srcs/data
```

---

## 🚀 Production Deployment

### Security Checklist

- [ ] Change `JWT_SECRET` in `.env` (use `openssl rand -base64 32`)
- [ ] Use SSL certificates from a valid CA (Let's Encrypt)
- [ ] ModSecurity in `SecRuleEngine On` mode (blocking)
- [ ] Change Vault root token after initialization
- [ ] Disable Vault debug logs
- [ ] Configure automatic backups for `srcs/data/` and `srcs/secrets/`
- [ ] Set up firewall (UFW/iptables) to restrict port access
- [ ] Enable fail2ban to block IPs with failed login attempts
- [ ] Configure HTTPS Strict Transport Security (HSTS)
- [ ] Implement Content Security Policy (CSP)

### Production Environment Variables

```bash
# .env (production)
JWT_SECRET=$(openssl rand -base64 32)
JWT_REFRESH_SECRET=$(openssl rand -base64 32)
DATABASE_URL=postgresql://user:pass@db:5432/transcendence  # Migrate to PostgreSQL
VAULT_ADDR=https://vault.transcendence.com:8200
NODE_ENV=production
LOG_LEVEL=warn
```

---

**Location**: `/srcs/`  
**Technologies**: Nginx, ModSecurity WAF, HashiCorp Vault, OpenSSL, Bash  
**Related documentation**:
- `conf/README.md` - Nginx + ModSecurity configuration
- `secrets/README.md` - Secrets management
- `scripts/README.md` - Automation
- `/docker-compose.yml` - Service orchestration
- `/backend/` - Backend integration
- `/frontend/` - Frontend integration