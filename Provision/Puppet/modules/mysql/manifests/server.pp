include apt

class mysql::server {

	$rootPassword = "@dm1n"

	exec { "python-software-installation":
		command	=> "sudo apt-get install -y --force-yes python-software-properties",
		path	=> [ "/usr/bin", "/bin" ],
	}

	package { "mysql-server":
			ensure	=> installed,
	} ->

	service { "mysql":
		ensure      => running,
		enable      => true,
		hasstatus   => true,
		hasrestart  => true,
		require		=> Package["mysql-server"],
	} ->

	exec { "set-mysql-password":
			require => Service["mysql"],
			unless => "mysqladmin -uroot -p$rootPassword status",
			path => ["/bin", "/usr/bin"],
			command => "mysqladmin -uroot password $rootPassword",
	} ->

	exec { "remove-anonymous-user":
			command	=> "mysql -uroot -e \"DELETE FROM mysql.user \
																		WHERE user = ' '; \
																		FLUSH PRIVILEGES\"",
			onlyif	=> "mysql -u' '",
			path	=> "/usr/bin",
			require	=> Service["mysql"],
	}

}
