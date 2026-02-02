FROM alpine:3.21.4

ARG DB_NAME
ARG DB_USER
ARG DB_PASS
ARG DB_ROOT

RUN apk update && apk add --no-cache mariadb mariadb-client

RUN mkdir -p /var/run/mysqld && chown mysql:mysql /var/run/mysqld
RUN mkdir -p /etc/my.cnf.d && echo '[mysqld]\nskip-host-cache\nskip-name-resolve\nbind-address=0.0.0.0' > /etc/my.cnf.d/docker.cnf

RUN echo '[mysqld]\nauth_socket=OFF\n default_authentication_plugin=mysql_native_password' > /etc/my.cnf.d/auth.cnf

RUN sed -i 's/^skip-networking/#skip-networking/' /etc/my.cnf.d/mariadb-server.cnf

RUN mariadb-install-db --user=mysql --datadir=/var/lib/mysql --auth-root-authentication-method=normal
EXPOSE 3306
COPY conf/db.sh .
RUN sh db.sh

USER mysql

CMD ["/usr/bin/mariadbd", "--skip-log-error", "--skip-grant-tables=false"]