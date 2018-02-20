#!/bin/bash

sudo apt-get update
sudo apt-get install --yes puppet

echo "export POCO_API_ENVIRONMENT=development" >> /home/vagrant/.profile
echo "export POCO_API_ENVIRONMENT=development" >> /home/vagrant/.bashrc

sed -i 's|[#]*PasswordAuthentication no|PasswordAuthentication yes|g' /etc/ssh/sshd_config
service ssh restart
