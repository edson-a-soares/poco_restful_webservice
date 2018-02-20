
include apt

class mysql::server {

    $root_password = "@dm1n"

    exec { "set-mysql-password":
      unless 	=> "test -f /etc/mysql/mysql.conf.d/mysqld.cnf",
      command => "echo debconf mysql-server/root_password password $root_password | sudo debconf-set-selections \
                    && echo debconf mysql-server/root_password_again password $root_password | sudo debconf-set-selections",
      path 		=> ["/bin", "/usr/bin"],
    } ->

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

    exec { "remove-anonymous-user":
        command	=> "mysql -uroot -e \"DELETE FROM mysql.user \
                                          WHERE user = ' '; \
                                          FLUSH PRIVILEGES\"",
        onlyif	=> "mysql -u' '",
        path		=> "/usr/bin",
        require	=> Service["mysql"],
    } ->

    exec { "allow-remote-access":
        command 	=> "mysql -uroot -p$root_password -e \"GRANT ALL PRIVILEGES ON \
                                                            *.* TO 'root'@'%' \
                                                            IDENTIFIED BY '$root_password'; \
                                                            FLUSH PRIVILEGES\"",
        path		    => "/usr/bin",
        require 		=> Package["mysql-server"],
        refreshonly => true,
    } ->

    file { "/etc/mysql/mysql.conf.d/mysqld.cnf":
        ensure	=> file,
        source	=> "puppet:///modules/mysql/my.cnf",
        group	  => root,
        owner	  => root,
        mode		=> '644'
    } ->

    exec { "restart-mysql":
        command     => "sudo service mysql restart",
        require     => Package["mysql-server"],
        subscribe   => File["/etc/mysql/mysql.conf.d/mysqld.cnf"],
        refreshonly => true,
        path 		    => [ "/bin", "/usr/bin" ],
    }

}
