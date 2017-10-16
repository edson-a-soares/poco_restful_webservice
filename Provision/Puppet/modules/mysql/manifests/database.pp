define mysql::database ($schema, $user = $title, $password, $rootPassword = "@dm1n") {
    Class['mysql::server'] -> Mysql::Database[$title]

    exec { "schema-$title":
        unless  => "mysql -uroot -p$rootPassword $schema",
        command => "mysql -uroot -p$rootPassword -e \"CREATE DATABASE $schema DEFAULT CHARACTER SET utf8 COLLATE utf8_bin\"",
        path    => "/usr/bin/",
    }

    exec { "user-$title":
        unless  => "mysql -u$user -p$password $schema",
        command => "mysql -uroot -p$rootPassword -e \"GRANT ALL PRIVILEGES ON \
            $schema.* TO '$user'@'localhost' \
            IDENTIFIED BY '$password' \
            WITH GRANT OPTION; \
            GRANT ALL PRIVILEGES ON \
            $schema.* TO '$user'@'%' \
            IDENTIFIED BY '$password' \
            WITH GRANT OPTION; \
            FLUSH PRIVILEGES\"",
        path    => "/usr/bin/",
        require => Exec["schema-$title"],
    }

}
