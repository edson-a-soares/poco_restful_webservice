
    VAGRANTFILE_API_VERSION = "2"

    MANIFEST = "default.pp"
    MANIFESTS_PATH = "provision/puppet/manifests"
    CUSTOM_MODULES_PATH = "provision/puppet/modules"
    LIBRARIAN_MODULES_PATH = "provision/puppet/librarian/modules"

    Vagrant.configure(VAGRANTFILE_API_VERSION) do |config|

        # Virtualbox environment
        config.vm.define :sample_hosting do |sh|

            sh.vm.box = "ubuntu/precise32"
            sh.vm.hostname = "poco-sample-hosting"
            sh.vm.network :private_network, ip: "192.168.1.100"
            sh.vm.network "forwarded_port", guest: 9000, host: 9000, auto_correct: true

            sh.ssh.forward_agent = true
            sh.ssh.insert_key = false

            sh.vm.provider :virtualbox do |virtualbox|

                virtualbox.customize [
                    "modifyvm", :id,
                    "--memory", "1024",
                    "--cpus", "1",
                    "--hwvirtex", "off",
                    "--pae", "on",
                    "--ioapic", "off",
                    "--natdnsproxy1", "on",
                    "--natdnshostresolver1", "on"
                ]

            end

        end

        # provisioning directives
        config.vm.provision "shell" do |local_userdata|
            local_userdata.path = "provision/shell/bootloader.sh"
            local_userdata.privileged = "yes"
        end

        config.vm.provision "puppet" do |puppet|

            puppet.manifests_path = MANIFESTS_PATH
            puppet.manifest_file  = MANIFEST
            puppet.module_path = [ LIBRARIAN_MODULES_PATH, CUSTOM_MODULES_PATH ]

            puppet.facter = {
                # Specifying the LANG environment variable this way is a work around.
                "hack=hack LANG=en_US.UTF-8 hack" => "hack"
            }

        end

    end
