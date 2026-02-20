# ⚙️ SRCS/CONF - Infrastructure Configuration

## 📋 General Overview

This directory contains the **configuration files** for the infrastructure services that protect and optimize the Transcendence application. It includes configurations for **Nginx** (reverse proxy + load balancer) and **ModSecurity** (Web Application Firewall - WAF) with OWASP CRS rules.

## 🗂️ Directory Structure

```
conf/
├── nginx/                    # Nginx configuration
│   ├── nginx.conf           # Main configuration file
│   ├── entrypoint-empty/    # Initialization scripts (currently empty)
│   └── templates-empty/     # Configuration templates (empty)
│
└── modsecurity/             # Web Application Firewall
    ├── modsecurity.conf     # Main ModSecurity configuration
    ├── crs-setup.conf       # OWASP CRS configuration
    ├── unicode.mapping      # Unicode character mapping
    ├── custom-rules/        # Project custom rules
    ├── custom-rules-options/# Custom rules options
    └── owasp-crs/          # Complete OWASP Core Rule Set
```

## 🌐 Nginx - Reverse Proxy and Load Balancer

### `nginx.conf` - Main Configuration

**Purpose**: Act as a single entry point for all HTTP/HTTPS requests to the application.

#### Features

1. **Reverse Proxy**: Forwards requests to backend/frontend based on the route
2. **SSL/TLS Termination**: Manages HTTPS certificates
3. **Load Balancing**: Distributes load across multiple instances (ready for scaling)
4. **Compression**: Gzip to reduce response size
5. **Caching**: Static asset cache
6. **Security Headers**: HTTP security headers

#### Typical Structure

```nginx
# nginx.conf

user nginx;
worker_processes auto;
error_log /var/log/nginx/error.log warn;
pid /var/run/nginx.pid;

events {
    worker_connections 1024;
    use epoll;  # Linux optimization
}

http {
    include /etc/nginx/mime.types;
    default_type application/octet-stream;

    # Logging
    log_format main '$remote_addr - $remote_user [$time_local] "$request" '
                    '$status $body_bytes_sent "$http_referer" '
                    '"$http_user_agent" "$http_x_forwarded_for"';
    access_log /var/log/nginx/access.log main;

    # Performance
    sendfile on;
    tcp_nopush on;
    tcp_nodelay on;
    keepalive_timeout 65;
    types_hash_max_size 2048;

    # Gzip compression
    gzip on;
    gzip_vary on;
    gzip_proxied any;
    gzip_comp_level 6;
    gzip_types text/plain text/css text/xml text/javascript 
               application/json application/javascript application/xml+rss;

    # Security headers
    add_header X-Frame-Options "SAMEORIGIN" always;
    add_header X-Content-Type-Options "nosniff" always;
    add_header X-XSS-Protection "1; mode=block" always;
    add_header Referrer-Policy "no-referrer-when-downgrade" always;

    # Rate limiting
    limit_req_zone $binary_remote_addr zone=api:10m rate=10r/s;
    limit_conn_zone $binary_remote_addr zone=addr:10m;

    # Upstream backends
    upstream backend {
        least_conn;  # Load balancing algorithm
        server backend:3000 max_fails=3 fail_timeout=30s;
        # server backend2:3000;  # For horizontal scaling
    }

    upstream frontend {
        server frontend:5173;
    }

    # HTTP → HTTPS redirect
    server {
        listen 80;
        server_name transcendence.local;
        return 301 https://$server_name$request_uri;
    }

    # HTTPS server
    server {
        listen 443 ssl http2;
        server_name transcendence.local;

        # SSL certificates
        ssl_certificate /etc/nginx/certs/fullchain.pem;
        ssl_certificate_key /etc/nginx/certs/privkey.pem;
        ssl_protocols TLSv1.2 TLSv1.3;
        ssl_ciphers HIGH:!aNULL:!MD5;
        ssl_prefer_server_ciphers on;
        ssl_session_cache shared:SSL:10m;
        ssl_session_timeout 10m;

        # ModSecurity integration
        modsecurity on;
        modsecurity_rules_file /etc/nginx/modsec/modsecurity.conf;

        # API endpoints → Backend
        location /api/ {
            limit_req zone=api burst=20 nodelay;
            proxy_pass http://backend;
            proxy_http_version 1.1;
            proxy_set_header Upgrade $http_upgrade;
            proxy_set_header Connection 'upgrade';
            proxy_set_header Host $host;
            proxy_set_header X-Real-IP $remote_addr;
            proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
            proxy_set_header X-Forwarded-Proto $scheme;
            proxy_cache_bypass $http_upgrade;
        }

        # Socket.IO → Backend
        location /socket.io/ {
            proxy_pass http://backend;
            proxy_http_version 1.1;
            proxy_set_header Upgrade $http_upgrade;
            proxy_set_header Connection "upgrade";
            proxy_set_header Host $host;
            proxy_read_timeout 86400;  # 24 hours for persistent connections
        }

        # Frontend SPA
        location / {
            proxy_pass http://frontend;
            proxy_set_header Host $host;
            proxy_set_header X-Real-IP $remote_addr;
            
            # SPA routing: redirect 404 to index.html
            try_files $uri $uri/ /index.html;
        }

        # Static assets with aggressive caching
        location ~* \.(jpg|jpeg|png|gif|ico|css|js|svg|woff|woff2|ttf|eot)$ {
            proxy_pass http://frontend;
            expires 1y;
            add_header Cache-Control "public, immutable";
        }

        # Health check endpoint
        location /healthz {
            access_log off;
            return 200 "OK\n";
            add_header Content-Type text/plain;
        }
    }
}
```

#### Rate Limiting

```nginx
# Limit login attempts
limit_req_zone $binary_remote_addr zone=login:10m rate=5r/m;

location /api/auth/login {
    limit_req zone=login burst=2 nodelay;
    proxy_pass http://backend;
}

# Limit room creation
limit_req_zone $binary_remote_addr zone=createroom:10m rate=10r/m;

location /api/rooms/create {
    limit_req zone=createroom burst=5;
    proxy_pass http://backend;
}
```

#### Load Balancing Strategies

```nginx
# 1. Round Robin (default)
upstream backend {
    server backend1:3000;
    server backend2:3000;
    server backend3:3000;
}

# 2. Least Connections (best for uneven loads)
upstream backend {
    least_conn;
    server backend1:3000;
    server backend2:3000;
}

# 3. IP Hash (sticky sessions)
upstream backend {
    ip_hash;
    server backend1:3000;
    server backend2:3000;
}

# 4. Weighted (servers with different capacities)
upstream backend {
    server backend1:3000 weight=3;
    server backend2:3000 weight=1;
}
```

---

## 🛡️ ModSecurity - Web Application Firewall

### `modsecurity.conf` - Main Configuration

**Purpose**: Enable and configure the ModSecurity engine to inspect HTTP traffic.

#### Base Configuration

```apache
# modsecurity.conf

# Enable ModSecurity
SecRuleEngine On

# Working directories
SecDataDir /tmp/
SecTmpDir /tmp/

# Logging
SecAuditEngine RelevantOnly
SecAuditLogRelevantStatus "^(?:5|4(?!04))"
SecAuditLogParts ABIJDEFHZ
SecAuditLogType Serial
SecAuditLog /var/log/modsec/modsec_audit.log

# Request body inspection
SecRequestBodyAccess On
SecRequestBodyLimit 13107200  # 12.5 MB
SecRequestBodyNoFilesLimit 131072  # 128 KB
SecRequestBodyLimitAction Reject

# Response body inspection
SecResponseBodyAccess On
SecResponseBodyMimeType text/plain text/html text/xml application/json
SecResponseBodyLimit 524288  # 512 KB
SecResponseBodyLimitAction ProcessPartial

# Debugging
SecDebugLog /var/log/modsec/modsec_debug.log
SecDebugLogLevel 0  # 0=off, 9=verbose

# Upload restrictions
SecUploadDir /tmp/
SecUploadKeepFiles Off

# Connection limits
SecConnEngine Off  # Disabled by default

# Rule engine
SecRuleEngine On
SecRequestBodyAccess On
SecRule REQUEST_HEADERS:Content-Type "text/xml" \
    "id:'200000',phase:1,t:none,t:lowercase,pass,nolog,ctl:requestBodyProcessor=XML"
```

### `crs-setup.conf` - OWASP CRS Setup

**Purpose**: Configure the OWASP Core Rule Set with anomaly scoring policies.

#### Anomaly Scoring

```apache
# crs-setup.conf

# Paranoia level (1-4)
# 1: Basic, 2: Moderate, 3: Strict, 4: Extreme
SecAction \
  "id:900000,\
   phase:1,\
   nolog,\
   pass,\
   t:none,\
   setvar:tx.paranoia_level=2"

# Anomaly thresholds
SecAction \
  "id:900110,\
   phase:1,\
   nolog,\
   pass,\
   t:none,\
   setvar:tx.inbound_anomaly_score_threshold=5,\
   setvar:tx.outbound_anomaly_score_threshold=4"

# Blocking mode
SecAction \
  "id:900200,\
   phase:1,\
   nolog,\
   pass,\
   t:none,\
   setvar:tx.blocking_paranoia_level=2"
```

#### Application Whitelisting

```apache
# Allow certain endpoints without inspection (use with caution)
SecRule REQUEST_URI "@beginsWith /api/healthz" \
    "id:900900,\
     phase:1,\
     pass,\
     nolog,\
     ctl:ruleEngine=Off"

# Exclude Socket.IO from body inspection
SecRule REQUEST_URI "@beginsWith /socket.io/" \
    "id:900901,\
     phase:1,\
     pass,\
     nolog,\
     ctl:requestBodyAccess=Off"
```

---

## 📁 Subdirectories

### `custom-rules/`

**Purpose**: Custom rules specific to Transcendence.

**Content**: See [modsecurity/custom-rules/README.md](./modsecurity/custom-rules/README.md) for details on the 18+ custom rules.

**Examples**:
- `900450-login-ratelimit.conf`: Rate limiting for authentication endpoints
- `900300-upload-guard.conf`: Avatar upload validation
- `900100-allow-static-bypass.conf`: Rule bypass for static assets

### `custom-rules-options/`

**Purpose**: Options and auxiliary configurations for custom rules.

### `owasp-crs/`

**Purpose**: Complete OWASP Core Rule Set (3000+ rules).

**Categories**:
- **REQUEST-901**: Initialization
- **REQUEST-920**: Protocol Enforcement
- **REQUEST-921**: Protocol Attack
- **REQUEST-930**: Application Attack (LFI)
- **REQUEST-931**: Application Attack (RFI)
- **REQUEST-932**: Application Attack (RCE)
- **REQUEST-933**: Application Attack (PHP)
- **REQUEST-941**: Application Attack (XSS)
- **REQUEST-942**: Application Attack (SQLi)
- **RESPONSE-950**: Data Leakages
- **RESPONSE-980**: Correlation

---

## 🔗 Nginx + ModSecurity Integration

### Request Flow

```
Client → HTTPS Request
    ↓
Nginx (port 443)
    ↓
ModSecurity WAF (inspection)
    ├─ Threat detected?
    │   ├─ Yes → 403 Forbidden (blocked)
    │   └─ No → Continue
    ↓
Nginx Proxy Pass
    ├─ /api/* → Backend (port 3000)
    ├─ /socket.io/* → Backend (WebSocket)
    └─ /* → Frontend (port 5173)
    ↓
Response ← Backend/Frontend
    ↓
ModSecurity (response inspection)
    ↓
Nginx → Client
```

### Integrated Logging

```nginx
# nginx.conf - Logs with ModSecurity info
log_format modsec '$remote_addr - $remote_user [$time_local] '
                  '"$request" $status $body_bytes_sent '
                  '"$http_referer" "$http_user_agent" '
                  'modsec_audit_id="$modsec_audit_id" '
                  'modsec_score="$modsec_score"';

access_log /var/log/nginx/access_modsec.log modsec;
```

---

## 🚀 Deployment and Testing

### Validate Nginx Configuration

```bash
# Syntax test
nginx -t

# Reload without downtime
nginx -s reload

# View active configuration
nginx -T
```

### Validate ModSecurity Rules

```bash
# Test individual rules
modsec-rules-check /etc/nginx/modsec/modsecurity.conf

# View loaded rules
grep -r "SecRule" /etc/nginx/modsec/
```

### WAF Testing

```bash
# XSS test (should be blocked)
curl -k "https://localhost/api/users?search=<script>alert(1)</script>"

# SQLi test (should be blocked)
curl -k "https://localhost/api/users?id=1' OR '1'='1"

# LFI test (should be blocked)
curl -k "https://localhost/api/files?path=../../../../etc/passwd"

# View ModSecurity logs
tail -f /var/log/modsec/modsec_audit.log
```

---

## 📊 Monitoring

### Nginx Metrics

```nginx
# Stub status module
location /nginx_status {
    stub_status;
    access_log off;
    allow 127.0.0.1;
    deny all;
}
```

Output:
```
Active connections: 42
server accepts handled requests
 1234 1234 5678
Reading: 0 Writing: 5 Waiting: 37
```

### ModSecurity Alerts

```bash
# Attack monitoring script
#!/bin/bash
tail -f /var/log/modsec/modsec_audit.log | \
grep -E "id \"(942100|941100|930100)\"" | \
while read line; do
    echo "ALERT: Attack detected - $line"
    # Send notification (email, Slack, etc.)
done
```

---

## 🔧 Optimization

### Nginx Performance Tuning

```nginx
# Increase worker connections
events {
    worker_connections 4096;
}

# File descriptor limits
worker_rlimit_nofile 8192;

# Proxy caching
proxy_cache_path /var/cache/nginx levels=1:2 keys_zone=api_cache:10m max_size=1g inactive=60m;

location /api/ {
    proxy_cache api_cache;
    proxy_cache_valid 200 5m;
    proxy_cache_use_stale error timeout updating;
    add_header X-Cache-Status $upstream_cache_status;
}
```

### ModSecurity Performance

```apache
# Reduce paranoia level in production if there are false positives
setvar:tx.paranoia_level=1

# Disable inspection for certain content types
SecRule RESPONSE_CONTENT_TYPE "@rx ^image/(jpeg|png|gif)" \
    "id:900950,phase:3,pass,nolog,ctl:responseBodyAccess=Off"
```

---

**Location**: `/srcs/conf/`  
**Technologies**: Nginx 1.25, ModSecurity 3, OWASP CRS 4  
**Related documentation**:
- `modsecurity/custom-rules/README.md` - Custom rules
- `../secrets/certs/README.md` - SSL/TLS certificates
- `/docker-compose.yml` - Container integration