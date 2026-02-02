#!/bin/sh

# Check if wp-config.php doesn't exist in WordPress root directory
if [ ! -f "/var/www/html/wp-config.php" ]; then
    # Use heredoc to create wp-config.php with dynamic values from environment variables
    cat << EOF > /var/www/html/wp-config.php
<?php
# Database connection settings
define( 'DB_NAME', '${DB_NAME}' );          # Database name from environment variable
define( 'DB_USER', '${DB_USER}' );          # Database user from environment variable
define( 'DB_PASSWORD', '${DB_PASS}' );      # Database password from environment variable
define( 'DB_HOST', 'mariadb' );             # Hostname of MariaDB container (Docker service name)
define( 'DB_CHARSET', 'utf8' );             # Default database charset
define( 'DB_COLLATE', '' );                 # No custom collation

# Filesystem method - allows direct filesystem writes (needed for Docker)
define('FS_METHOD','direct');

# Force SSL for admin area and detect HTTPS from proxy headers
define('FORCE_SSL_ADMIN', true);
if (isset(\$_SERVER['HTTP_X_FORWARDED_PROTO']) && \$_SERVER['HTTP_X_FORWARDED_PROTO'] == 'https') {
    \$_SERVER['HTTPS'] = 'on';  # Set HTTPS flag when behind a proxy with SSL termination
}

# WordPress database table prefix (change for security)
\$table_prefix = 'wp_';

# Debug mode - disabled in production
define( 'WP_DEBUG', false );

# Define absolute path to WordPress directory
if ( ! defined( 'ABSPATH' ) ) {
    define( 'ABSPATH', __DIR__ . '/' );
}

# Load WordPress settings
require_once ABSPATH . 'wp-settings.php';
EOF

    echo "wp-config.php created successfully."
else
    echo "wp-config.php already exists. Skipping creation."
fi