
include apt

class mysql::server {

    $root_password = "@dm1n"

    package { "mysql-server":
        ensure	=> installed,
    } ->

    service { "mysql":
        ensure      => running,
        enable      => true,
        hasstatus   => true,
        hasrestart  => true,
        require			=> Package["mysql-server"],
    } ->

    exec { "set-mysql-password":
        require => Service["mysql"],
        unless 	=> "mysqladmin -uroot -p$root_password status",
        command => "mysqladmin -uroot password $root_password",
        path 		=> ["/bin", "/usr/bin"],
    } ->

    exec { "remove-anonymous-user":
        command	=> "mysql -uroot -e \"DELETE FROM mysql.user \
                                                WHERE user = ' '; \
                                                FLUSH PRIVILEGES\"",
        onlyif	=> "mysql -u' '",
        path		=> "/usr/bin",
        require	=> Service["mysql"],
    }

    exec { "allow-remote-access":
        command 	=> "mysql -uroot -p$root_password -e \"GRANT ALL PRIVILEGES ON \
                                                *.* TO 'root'@'%' \
                                                IDENTIFIED BY '$root_password'; \
                                                FLUSH PRIVILEGES\"",
        path		=> "/usr/bin",
        require 		=> Package["mysql-server"],
        refreshonly => true,
    } ->

    file { "/etc/mysql/my.cnf":
        ensure	=> file,
        source	=> "puppet:///modules/mysql/my.cnf",
        group	  => root,
        owner	  => root,
        mode		=> '644'
    } ->

    exec { "restart-mysql":
        command 		=> "sudo service mysql restart",
        require 		=> Package["mysql-server"],
        path 				=> [ "/bin", "/usr/bin" ],
    }

}