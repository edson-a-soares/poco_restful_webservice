define mysql::create_user ($username, $password, $host_grant = "%", $schema_grant = ".", $root_password = "@dm1n") {

    exec { "create-$username":
        command => "mysql -uroot -p$root_password -e \"GRANT ALL PRIVILEGES ON \
                *$schema_grant* TO '$username'@'$host_grant' \
                IDENTIFIED BY '$password'; \
                FLUSH PRIVILEGES\"",
        path    => "/usr/bin",
        require => Class['mysql::server']
    }

}
