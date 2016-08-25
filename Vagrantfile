# -*- mode: ruby -*-

NAME = "sta"

MIRRORS = <<SCRIPT
echo "###### Ubuntu Main Repos
deb http://de.archive.ubuntu.com/ubuntu/ trusty main restricted universe multiverse
deb-src http://de.archive.ubuntu.com/ubuntu/ trusty main restricted universe multiverse

###### Ubuntu Update Repos
deb http://de.archive.ubuntu.com/ubuntu/ trusty-security main restricted universe multiverse
deb http://de.archive.ubuntu.com/ubuntu/ trusty-updates main restricted universe multiverse
deb http://de.archive.ubuntu.com/ubuntu/ trusty-proposed main restricted universe multiverse
deb http://de.archive.ubuntu.com/ubuntu/ trusty-backports main restricted universe multiverse
deb-src http://de.archive.ubuntu.com/ubuntu/ trusty-security main restricted universe multiverse
deb-src http://de.archive.ubuntu.com/ubuntu/ trusty-updates main restricted universe multiverse
deb-src http://de.archive.ubuntu.com/ubuntu/ trusty-proposed main restricted universe multiverse
deb-src http://de.archive.ubuntu.com/ubuntu/ trusty-backports main restricted universe multiverse" > /etc/apt/sources.list
SCRIPT

UPGRADE = <<SCRIPT
# Update system
apt-get -y update
apt-get -y dist-upgrade
apt-get -y upgrade
SCRIPT

DEVTOOLS = <<SCRIPT
apt-get -y install vim man wget
SCRIPT

DESKTOP = <<SCRIPT
apt-get -y install xfce4
# apt-get -y install virtualbox-guest-dkms virtualbox-guest-utils virtualbox-guest-x11
# apt-get -y install ubuntu-gnome-desktop gnome-shell
apt-get -y install git build-essential libsdl2-dev libsdl2-gfx-dev libsdl2-ttf-dev
SCRIPT

Vagrant.configure("2") do |config|
  config.vm.box = "ubuntu/trusty64"
  config.vm.hostname = NAME

  config.vm.provision :shell, inline: MIRRORS, keep_color: true
  config.vm.provision :shell, inline: UPGRADE, keep_color: true
  config.vm.provision :shell, inline: DEVTOOLS, keep_color: true

  config.vm.provider "virtualbox" do |vb|
    vb.name = NAME
    vb.memory = 1024
    vb.gui = true
  end
end