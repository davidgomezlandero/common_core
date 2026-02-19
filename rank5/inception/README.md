# Inception

## Table of Contents
1. [Overview](#overview)
2. [Infrastructure](#infrastructure)
3. [How It Works](#how-it-works)
4. [Project Structure](#project-structure)
5. [Services](#services)
   - [Nginx](#nginx)
   - [WordPress](#wordpress)
   - [MariaDB](#mariadb)
6. [Volumes & Network](#volumes--network)
7. [Environment Variables](#environment-variables)
8. [Implementation Details](#implementation-details)
   - [Nginx Configuration](#nginx-configuration)
   - [TLS Certificate Generation](#tls-certificate-generation)
   - [MariaDB Initialisation](#mariadb-initialisation)
   - [WordPress Initialisation](#wordpress-initialisation)
   - [Container Startup Order](#container-startup-order)
9. [Build & Run](#build--run)

---

## Overview

Inception is a system administration project. The goal is to build a complete
multi-service web infrastructure entirely inside Docker containers, where
**every container is built from scratch** using custom `Dockerfile`s based on
the penultimate stable release of **Debian**.

No pre-built service images (`nginx:latest`, `wordpress:latest`, etc.) are
used. All configuration is automated — the full infrastructure comes up with
a single `make` command.

---

## Infrastructure

```
Browser  (HTTPS :443)
    │
    ▼
┌─────────────────────────────────┐
│         Nginx container         │  ← TLS termination, static files,
│         Port 443 (host)         │    FastCGI proxy to WordPress
└────────────────┬────────────────┘
                 │ FastCGI :9000
                 ▼
┌─────────────────────────────────┐
│       WordPress container       │  ← PHP-FPM + WP-CLI
│  (not exposed to host)          │    serves dynamic PHP requests
└────────────────┬────────────────┘
                 │ TCP :3306
                 ▼
┌─────────────────────────────────┐
│        MariaDB container        │  ← Database server
│  (not exposed to host)          │    persistent data on named volume
└─────────────────────────────────┘

Named volumes (host: /home/davigome/data/):
    ├── wordpress_data  →  /var/www/html        (shared Nginx ↔ WordPress)
    └── db_data         →  /var/lib/mysql        (MariaDB data)

Internal bridge network: inception_net
    └── containers communicate by service name (mariadb, wordpress, nginx)
```

---

## How It Works

```
make
 └── docker-compose up --build
         │
         ├── Build MariaDB image
         │       └── Container starts → create_db.sh:
         │               mysqld --bootstrap < init.sql
         │               Creates DB, user, grants, sets root password
         │               Then runs: mysqld_safe (foreground)
         │
         ├── Build WordPress image
         │       └── Container starts → wp-config-create.sh:
         │               Loop: ping MariaDB until ready
         │               Generate wp-config.php with DB credentials
         │               wp core download (if not present)
         │               wp core install (title, admin, url)
         │               wp user create (regular user)
         │               exec php-fpm (foreground, non-daemon)
         │
         └── Build Nginx image
                 └── Container starts:
                         Certificate already generated at build time
                         nginx -g "daemon off;" (foreground)
                         Listens on :443 TLS only
                         Serves /var/www/html static files
                         Proxies *.php → wordpress:9000 via FastCGI
```

---

## Project Structure

```
inception/
├── Makefile                               # up / down / fclean targets
├── make_directories.sh                    # scaffold script (used once)
└── srcs/
    ├── docker-compose.yml                 # Service definitions, volumes, network
    ├── .env                               # All runtime configuration
    └── requirements/
        ├── nginx/
        │   ├── Dockerfile                 # Debian + nginx + openssl
        │   ├── conf/
        │   │   └── nginx.conf             # HTTPS server block, FastCGI config
        │   └── tools/
        │       └── create_cert.sh         # Self-signed TLS cert generation
        ├── mariadb/
        │   ├── Dockerfile                 # Debian + mariadb-server
        │   └── conf/
        │       └── create_db.sh           # DB + user creation at startup
        └── wordpress/
            ├── Dockerfile                 # Debian + php-fpm + WP-CLI
            └── conf/
                └── wp-config-create.sh    # wp-config.php + WP installation
```

---

## Services

### Nginx

Built from Debian. Installed packages: `nginx`, `openssl`.

- A **self-signed TLS certificate** is generated at **build time** by
  [`tools/create_cert.sh`](srcs/requirements/nginx/tools/create_cert.sh)
  for the domain `davigome.42.fr` and copied into the image at
  `/etc/nginx/ssl/`.
- Configured to accept **only TLS 1.2 and TLS 1.3** — plain HTTP on port 80
  is not configured.
- Exposed on host port **443** only.
- Serves WordPress static files (PHP files excluded) directly from the
  shared `wordpress_data` volume mounted at `/var/www/html`.
- Proxies all `.php` requests to the **WordPress** container via **FastCGI**
  on port 9000, using `fastcgi_pass wordpress:9000`.
- Runs `nginx -g "daemon off;"` as the container's PID 1.

### WordPress

Built from Debian. Installed packages: `php-fpm`, `php-mysql`,
`php-cli`, and all PHP extensions required by WordPress core.
**WP-CLI** is downloaded and installed to `/usr/local/bin/wp`.

[`conf/wp-config-create.sh`](srcs/requirements/wordpress/conf/wp-config-create.sh)
runs at container startup and:

1. **Waits** for MariaDB by looping on `mysqladmin ping -h mariadb` until it
   succeeds.
2. **Downloads** WordPress core with `wp core download` if not already present.
3. **Generates** `wp-config.php` by running `wp config create` with the
   database credentials injected from environment variables.
4. **Installs** WordPress with `wp core install` — sets the site URL, title,
   admin username, admin password, and admin email from environment variables.
5. **Creates** a second (non-admin) user with `wp user create`.
6. **Launches** `php-fpm` in the foreground with `exec php-fpm -F` as the
   final step — this becomes PID 1.

Not exposed to the host — reachable only from Nginx on `inception_net`.

### MariaDB

Built from Debian. Installed packages: `mariadb-server`.

[`conf/create_db.sh`](srcs/requirements/mariadb/conf/create_db.sh) runs at
container startup:

1. Starts MariaDB in **bootstrap mode** (`mysqld --bootstrap`) to execute
   SQL statements before the server accepts connections.
2. Creates the application database (`$DB_NAME`).
3. Creates the application user (`$DB_USER`) with password (`$DB_PASS`)
   and grants all privileges on the database.
4. Sets the `root` password (`$DB_ROOT`) and flushes privileges.
5. Starts `mysqld_safe` in the foreground as PID 1.

Data is persisted on the `db_data` named volume mounted at `/var/lib/mysql`
so the database survives container restarts.

Not exposed to the host — reachable only from WordPress on `inception_net`.

---

## Volumes & Network

### Named Volumes

| Volume | Container mount | Shared between | Host path |
|--------|-----------------|----------------|-----------|
| `wordpress_data` | `/var/www/html` | Nginx (read) + WordPress (read/write) | `/home/davigome/data/wordpress` |
| `db_data` | `/var/lib/mysql` | MariaDB only | `/home/davigome/data/mariadb` |

The host paths are created automatically by the `Makefile` before
`docker-compose up`.

### Network

A single **bridge network** named `inception_net` connects all three
containers. Docker's embedded DNS resolves container names — WordPress
connects to MariaDB using the hostname `mariadb`, and Nginx connects to
WordPress using the hostname `wordpress`. No container except Nginx is
reachable from outside the Docker network.

---

## Environment Variables

All configuration lives in [`srcs/.env`](srcs/.env). Nothing is hardcoded
in Dockerfiles or scripts.

```env
DOMAIN_NAME=davigome.42.fr

CERT_=./requirements/tools/davigome.42.fr.crt
KEY_=./requirements/tools/davigome.42.fr.key

DB_NAME=wordpress
DB_ROOT=rootpass
DB_USER=wpuser
DB_PASS=wppass
```

`docker-compose.yml` injects these into each container's environment at
startup via the `environment:` block. Scripts read them as `$DB_NAME`,
`$DB_USER`, etc.

---

## Implementation Details

### Nginx Configuration

[`srcs/requirements/nginx/conf/nginx.conf`](srcs/requirements/nginx/conf/nginx.conf):

```nginx
server {
    listen      443 ssl;
    server_name davigome.42.fr;

    ssl_certificate     /etc/nginx/ssl/davigome.42.fr.crt;
    ssl_certificate_key /etc/nginx/ssl/davigome.42.fr.key;
    ssl_protocols       TLSv1.2 TLSv1.3;

    root  /var/www/html;
    index index.php index.html;

    location / {
        try_files $uri $uri/ /index.php?$args;
    }

    location ~ \.php$ {
        fastcgi_pass             wordpress:9000;
        fastcgi_index            index.php;
        include                  fastcgi_params;
        fastcgi_param SCRIPT_FILENAME $document_root$fastcgi_script_name;
    }
}
```

### TLS Certificate Generation

[`srcs/requirements/nginx/tools/create_cert.sh`](srcs/requirements/nginx/tools/create_cert.sh)
runs during the **Nginx image build** (not at runtime):

```bash
openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
    -keyout /etc/nginx/ssl/davigome.42.fr.key \
    -out    /etc/nginx/ssl/davigome.42.fr.crt \
    -subj   "/C=ES/ST=Madrid/L=Madrid/O=42/CN=davigome.42.fr"
```

The certificate and key are embedded in the image — no runtime dependency on
external certificate infrastructure.

### MariaDB Initialisation

[`srcs/requirements/mariadb/conf/create_db.sh`](srcs/requirements/mariadb/conf/create_db.sh):

```sql
CREATE DATABASE IF NOT EXISTS ${DB_NAME};
CREATE USER IF NOT EXISTS '${DB_USER}'@'%' IDENTIFIED BY '${DB_PASS}';
GRANT ALL PRIVILEGES ON ${DB_NAME}.* TO '${DB_USER}'@'%';
ALTER USER 'root'@'localhost' IDENTIFIED BY '${DB_ROOT}';
FLUSH PRIVILEGES;
```

Run via `mysqld --bootstrap` so MariaDB never opens a network port during
initialisation — only `mysqld_safe` started at the end accepts client
connections.

### WordPress Initialisation

[`srcs/requirements/wordpress/conf/wp-config-create.sh`](srcs/requirements/wordpress/conf/wp-config-create.sh):

```bash
# Wait for MariaDB
until mysqladmin ping -h mariadb --silent; do sleep 1; done

# Download core if absent
wp core download --path=/var/www/html --allow-root

# Generate wp-config.php
wp config create \
    --dbname=$DB_NAME --dbuser=$DB_USER --dbpass=$DB_PASS \
    --dbhost=mariadb  --path=/var/www/html --allow-root

# Install WordPress
wp core install \
    --url=https://$DOMAIN_NAME \
    --title="Inception" \
    --admin_user=$WP_ADMIN --admin_password=$WP_ADMIN_PASS \
    --admin_email=$WP_ADMIN_EMAIL \
    --path=/var/www/html --allow-root

# Create regular user
wp user create $WP_USER $WP_USER_EMAIL \
    --user_pass=$WP_USER_PASS --role=author \
    --path=/var/www/html --allow-root

exec php-fpm -F
```

### Container Startup Order

`docker-compose.yml` uses `depends_on` to enforce:

```
mariadb  →  wordpress  →  nginx
```

WordPress also has its internal MariaDB readiness loop, making the
dependency robust even if MariaDB takes longer than expected to initialise
on first run (initial bootstrap can take several seconds).

---

## Build & Run

```bash
# Build all images and start all containers
make

# Stop containers (volumes and images preserved)
make down

# Stop containers and delete all volumes and images
make fclean

# Useful commands
docker-compose -f srcs/docker-compose.yml logs -f
docker exec -it wordpress bash
docker exec -it mariadb mariadb -u root -p
docker exec -it nginx nginx -t
```

> **Local DNS**: add the domain to `/etc/hosts` if testing locally:
> ```bash
> echo "127.0.0.1 davigome.42.fr" | sudo tee -a /etc/hosts
> ```
> Then open **https://davigome.42.fr** in a browser.
> Accept the self-signed certificate warning.