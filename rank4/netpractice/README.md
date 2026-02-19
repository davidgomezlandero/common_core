# NetPractice

## Table of Contents
1. [Overview](#overview)
2. [What Is NetPractice](#what-is-netpractice)
3. [Concepts Learned](#concepts-learned)
   - [IP Addressing](#ip-addressing)
   - [Subnet Masks](#subnet-masks)
   - [CIDR Notation](#cidr-notation)
   - [Routing](#routing)
   - [Special Address Ranges](#special-address-ranges)
4. [How the Levels Work](#how-the-levels-work)
5. [Key Rules Applied to Solve the Levels](#key-rules-applied-to-solve-the-levels)

---

## Overview

NetPractice is a browser-based networking exercise. It presents **10 progressive
levels**, each showing a broken network diagram. The goal is to fix it by
correctly assigning IP addresses, subnet masks, and routes so that all hosts
can communicate as required.

There is no code to write — the deliverable is a correct network configuration
for each level, verified by the built-in checker.

---

## What Is NetPractice

Each level shows a diagram with:

- **Hosts** — end devices with an IP interface and a routing table.
- **Routers** — devices with multiple interfaces, each on a different network,
  with a routing table.
- **Switches** — layer-2 devices that connect hosts on the same network
  (no IP configuration needed on the switch itself).
- **The Internet** — a special node representing external connectivity,
  with its own routing entry.

Some fields are pre-filled and locked. Others are blank and must be filled in
correctly. The checker validates that every required communication path works.

---

## Concepts Learned

### IP Addressing

An **IPv4 address** is a 32-bit number written as four decimal octets:

```
192.168.1.10
```

Every interface on a network must have a unique IP address within its subnet.
Two hosts can communicate directly only if they are on the **same network** —
meaning their IP addresses, when ANDed with the subnet mask, produce the same
**network address**.

```
Host A:   192.168.1.10  &  255.255.255.0  =  192.168.1.0  ← network
Host B:   192.168.1.20  &  255.255.255.0  =  192.168.1.0  ← same network ✓
Host C:   192.168.2.5   &  255.255.255.0  =  192.168.2.0  ← different network ✗
```

### Subnet Masks

A subnet mask defines how many bits of an IP address identify the **network**
and how many identify the **host**:

```
255.255.255.0   →  24 network bits,  8 host bits  →  254 usable hosts
255.255.255.128 →  25 network bits,  7 host bits  →  126 usable hosts
255.255.255.192 →  26 network bits,  6 host bits  →   62 usable hosts
255.255.255.240 →  28 network bits,  4 host bits  →   14 usable hosts
255.255.255.252 →  30 network bits,  2 host bits  →    2 usable hosts
```

The **network address** (all host bits = 0) and the **broadcast address**
(all host bits = 1) cannot be assigned to a host.

### CIDR Notation

CIDR (Classless Inter-Domain Routing) expresses the subnet mask as a prefix
length after a `/`:

```
192.168.1.0/24   ≡   192.168.1.0  with mask  255.255.255.0
10.0.0.0/30      ≡   10.0.0.0    with mask  255.255.255.252
```

This notation is used in routing tables and was used throughout every level
of NetPractice.

### Routing

When a packet's destination is **not** on the local network, the host sends
it to its **default gateway** — a router interface on the same subnet.

A **routing table** maps destination networks to the next hop (gateway) or
outgoing interface:

```
Destination     Mask              Gateway         Interface
0.0.0.0         0.0.0.0           192.168.1.1     eth0    ← default route
10.0.0.0        255.255.255.252   192.168.1.1     eth0    ← specific route
```

- **Default route** (`0.0.0.0/0`) matches any destination — used when no more
  specific route exists.
- **Specific routes** match only packets destined for that exact network —
  they are preferred over the default route.
- A router uses the **most specific matching route** (longest prefix match).

### Special Address Ranges

| Range | Purpose |
|-------|---------|
| `127.0.0.0/8` | Loopback — cannot be assigned to an interface |
| `10.0.0.0/8` | Private range |
| `172.16.0.0/12` | Private range |
| `192.168.0.0/16` | Private range |
| `0.0.0.0` | Represents any / default in routing tables |

These were relevant when choosing valid IP addresses during the levels — private
ranges had to be used for internal networks and loopback addresses had to be
avoided.

---

## How the Levels Work

The 10 levels progress in difficulty:

| Levels | Scope |
|--------|-------|
| 1–3 | Single subnet, assign correct IPs and masks so hosts can communicate |
| 4–6 | Introduce routers — configure interfaces and default routes |
| 7–8 | Multiple routers, specific routes required to reach each subnet |
| 9–10 | Full topologies — routers chained together, routes to the Internet, all paths must work simultaneously |

Each level requires understanding not just individual host configuration but
the **entire path** a packet travels from source to destination.

---

## Key Rules Applied to Solve the Levels

1. **Two hosts on the same switch must be in the same subnet** — same network
   address after applying the mask.

2. **Two interfaces connected directly by a cable must be in the same subnet**
   — typically a `/30` with only 2 usable addresses.

3. **A host's gateway must be in the same subnet as the host** — the host must
   be able to reach the gateway directly.

4. **A router's routing table must have a route for every destination network**
   that hosts behind it need to reach — either a specific route or a default
   route pointing to the next router.

5. **Routes must not overlap incorrectly** — if two subnets have the same
   network address with different masks, only the most specific one matches.

6. **The Internet node's route** must cover the address range of the hosts that
   need external connectivity — often set as a specific network or default.

7. **Never assign the network address or broadcast address** to a host
   interface.

8. **All subnets in the same topology must be unique** — two different network
   segments cannot share the same network address.