#!/bin/bash

POCO_WEBSERVICE_ENVIRONMENT=$1

sed -i -e '$a export POCO_WEBSERVICE_ENVIRONMENT='$POCO_WEBSERVICE_ENVIRONMENT'' /etc/apache2/envvars
a2enmod poco



