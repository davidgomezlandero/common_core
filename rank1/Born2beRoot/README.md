# Born2beRoot

## Table of Contents
1. [Overview](#overview)
2. [What Is a Virtual Machine?](#what-is-a-virtual-machine)
3. [Operating System Choice](#operating-system-choice)
4. [Mandatory Configuration](#mandatory-configuration)
   - [Disk Partitioning & LVM](#disk-partitioning--lvm)
   - [SSH](#ssh)
   - [Firewall — UFW](#firewall--ufw)
   - [sudo Policy](#sudo-policy)
   - [Password Policy](#password-policy)
   - [Monitoring Script](#monitoring-script)
5. [Evaluation](#evaluation)
6. [Key Commands Cheat Sheet](#key-commands-cheat-sheet)
7. [Learning Goals](#learning-goals)

---

## Overview

Born2beRoot is a **system administration** project. Unlike every other project in
the Common Core, there is no C code to write — the deliverable is a configured and
running **Linux virtual machine**.

The goal is to set up a minimal server environment and harden it according to a
strict set of security rules. During the evaluation, you must be able to explain
every single configuration choice and demonstrate that it works correctly.

> ⚠️ **No VM snapshot or disk image is submitted.** A `signature.txt` file
> containing the SHA-1 hash of the virtual disk is submitted instead. The
> evaluator boots your VM live and interrogates it.

---

## What Is a Virtual Machine?

A **virtual machine (VM)** is a software emulation of a physical computer. A
**hypervisor** — VirtualBox or UTM — runs on the host OS and allocates a share of
CPU, RAM, and disk to the guest OS, which runs in complete isolation.

```
Host OS (your Mac / Linux)
└── Hypervisor (VirtualBox / UTM)
    └── Guest OS (Debian VM)
        ├── Encrypted LVM partitions
        ├── SSH server (port 4242)
        ├── UFW firewall
        └── monitoring.sh (cron)
```

VMs are the foundation of modern cloud infrastructure — every server you deploy on
AWS, GCP, or Azure runs inside a VM.

---

## Operating System Choice

| Option | Notes |
|--------|-------|
| **Debian** *(recommended)* | Stable, large community, `apt` package manager, simpler setup |
| **Rocky Linux** | RHEL-based, `dnf` package manager, `firewalld` instead of UFW |

The subject specifies **the latest stable version** of whichever OS you choose.
Debian is strongly recommended for first-timers — the subject hints at this.

---

## Mandatory Configuration

### Disk Partitioning & LVM

The VM must use **LVM** (Logical Volume Manager) with at least two encrypted
partitions:

```
sda
├── sda1   /boot          (primary, unencrypted — bootloader must be accessible)
└── sda5   LVM PV (encrypted with LUKS)
           └── LVMGroup VG
               ├── root     /
               ├── swap
               ├── home     /home
               ├── var      /var
               ├── srv      /srv
               ├── tmp      /tmp
               └── var-log  /var/log
```

LVM allows resizing, snapshotting, and managing partitions dynamically without
rebooting — a key skill for any sysadmin.

### SSH

- SSH daemon must run on **port 4242** exclusively.
- **Root login via SSH must be disabled** (`PermitRootLogin no`).
- Password authentication is allowed (no key requirement in the mandatory part).

```bash
# /etc/ssh/sshd_config key lines
Port 4242
PermitRootLogin no
```

Connect from host:
```bash
ssh username@127.0.0.1 -p 4242
```

### Firewall — UFW

Only **port 4242** must be open. All other incoming connections must be blocked.

```bash
ufw default deny incoming
ufw default allow outgoing
ufw allow 4242
ufw enable
```

### sudo Policy

`sudo` must be configured with the following rules (enforced via
`/etc/sudoers.d/`):

| Rule | Value |
|------|-------|
| Authentication attempts | Max **3** |
| Wrong password message | Custom message displayed |
| Input / output archived | Every sudo command logged to `/var/log/sudo/` |
| TTY mode | Required (`Defaults requiretty`) |
| Secure path | Restricted to system binaries only |

### Password Policy

Configured via `/etc/login.defs` and `pam_pwquality`:

| Parameter | Requirement |
|-----------|-------------|
| Maximum password age | **30** days |
| Minimum days before change | **2** days |
| Warning before expiry | **7** days |
| Minimum length | **10** characters |
| Must contain uppercase | Yes |
| Must contain digits | Yes |
| Max consecutive identical chars | **3** |
| May not contain username | Yes |
| Min characters different from old password | **7** (non-root) |

### Monitoring Script

A shell script `monitoring.sh` must broadcast system information to all logged-in
terminals **every 10 minutes** via `wall`, scheduled with `cron`.

Required information displayed:

```
#Architecture   : Linux hostname 5.10.0 #1 SMP x86_64 GNU/Linux
#CPU physical   : 1
#vCPU           : 1
#Memory Usage   : 123/987MB (12.46%)
#Disk Usage     : 1.2/8.6Gb (14%)
#CPU load       : 6.7%
#Last boot      : 2024-01-15 10:23
#LVM use        : yes
#Connections TCP : 1 ESTABLISHED
#User log       : 1
#Network        : IP 10.0.2.15 (08:00:27:xx:xx:xx)
#Sudo           : 42 cmd
```

Cron entry:
```bash
*/10 * * * * /usr/local/bin/monitoring.sh
```

---

## Evaluation

The evaluation is entirely **oral and practical** — an evaluator connects to your
VM live and asks you to:

1. Explain how a virtual machine works and why you chose your OS.
2. Demonstrate the partition layout (`lsblk`).
3. Show that UFW is active and only port 4242 is open.
4. Connect via SSH on port 4242 and prove root login is blocked.
5. Show the sudo log directory and explain each rule.
6. Create a new user, assign it to a group, and explain password policy.
7. Explain how `cron` works and temporarily modify the monitoring interval.
8. Interrupt `monitoring.sh` without modifying the cron table itself.

> The evaluator may also ask you to create new users, add them to groups, change
> the hostname, or explain the difference between `apt` and `aptitude`.

---

## Key Commands Cheat Sheet

```bash
# System info
uname -a
lsblk
ss -tunlp
who

# UFW
ufw status numbered
ufw allow / deny / delete

# SSH
systemctl status ssh
nano /etc/ssh/sshd_config
systemctl restart ssh

# Users & groups
sudo adduser username
sudo usermod -aG groupname username
sudo deluser username groupname
getent group groupname
chage -l username          # password expiry info

# sudo log
ls /var/log/sudo/
journalctl _COMM=sudo

# Cron
sudo crontab -e            # edit root crontab
sudo crontab -l            # list root crontab

# LVM
lvdisplay
vgdisplay
pvdisplay
```

---

## Learning Goals

- Understand the concept of virtualisation and how hypervisors work
- Partition disks with LVM and understand LUKS encryption
- Manage Linux users, groups, and privilege escalation with `sudo`
- Configure and harden an SSH server
- Set up a stateful firewall with UFW
- Enforce system-wide password policies via PAM
- Write shell scripts that gather and format system metrics
- Schedule automated tasks with `cron`
- Understand the difference between Debian and RHEL-based distributions
- Read, understand, and confidently explain every line of your configuration