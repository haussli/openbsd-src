#	$OpenBSD: Makefile.inc,v 1.68 2019/08/16 06:35:27 djm Exp $

.include <bsd.own.mk>

CFLAGS+=	-I${.CURDIR}/..
CFLAGS+=	-fstack-protector-all

CDIAGFLAGS=	-Wall
CDIAGFLAGS+=	-Wextra
CDIAGFLAGS+=	-Wformat-security
CDIAGFLAGS+=	-Wmissing-declarations
CDIAGFLAGS+=	-Wmissing-prototypes
CDIAGFLAGS+=	-Wpointer-arith
CDIAGFLAGS+=	-Wshadow
CDIAGFLAGS+=	-Wstrict-prototypes
CDIAGFLAGS+=	-Wunused
CDIAGFLAGS+=	-Wno-unused-parameter # Lots of these in protocol handlers.
.if ${COMPILER_VERSION:L} != "gcc3"
CDIAGFLAGS+=	-Wstrict-aliasing=2
CDIAGFLAGS+=	-Wold-style-definition
.endif

#CDIAGFLAGS+=	-Werror
#DEBUG=-g
#INSTALL_STRIP=

WARNINGS=yes

OPENSSL?=	yes

.if (${OPENSSL:L} == "yes")
CFLAGS+=	-DWITH_OPENSSL
.endif

CFLAGS+=	-DENABLE_PKCS11
.ifndef NOPIC
CFLAGS+=	-DHAVE_DLOPEN
.endif

SRCS_BASE+=	sshbuf.c
SRCS_BASE+=	sshbuf-getput-basic.c
SRCS_BASE+=	sshbuf-misc.c
SRCS_BASE+=	ssherr.c
SRCS_BASE+=	log.c
SRCS_BASE+=	xmalloc.c
SRCS_BASE+=	misc.c

.if (${OPENSSL:L} == "yes")
SRCS_KEX+=	dh.c
SRCS_KEX+=	kexdh.c
SRCS_KEX+=	kexecdh.c
SRCS_KEX+=	kexgex.c
SRCS_KEXC+=	kexgexc.c
SRCS_KEXS+=	kexgexs.c
.endif
SRCS_KEX+=	kexc25519.c
SRCS_KEX+=	smult_curve25519_ref.c
SRCS_KEX+=	kexgen.c
SRCS_KEX+=	kexsntrup4591761x25519.c
SRCS_KEX+=	sntrup4591761.c

SRCS_KEY+=	sshkey.c
SRCS_KEY+=	cipher.c
SRCS_KEY+=	cipher-chachapoly.c
SRCS_KEY+=	chacha.c
SRCS_KEY+=	poly1305.c
.if (${OPENSSL:L} == "yes")
SRCS_KEY+=	ssh-dss.c
SRCS_KEY+=	ssh-ecdsa.c
SRCS_KEY+=	ssh-rsa.c
SRCS_KEY+=	sshbuf-getput-crypto.c
SRCS_KEY+=	digest-openssl.c
.else
SRCS_KEY+=	cipher-aesctr.c
SRCS_KEY+=	rijndael.c
SRCS_KEY+=	digest-libc.c
.endif
SRCS_KEY+=	ssh-ed25519.c
# ed25519, from supercop
SRCS_KEY+=	sc25519.c
SRCS_KEY+=	ge25519.c
SRCS_KEY+=	fe25519.c
SRCS_KEY+=	ed25519.c
SRCS_KEY+=	verify.c
SRCS_KEY+=	hash.c

SRCS_KEYP+=	authfile.c

SRCS_KRL+=	bitmap.c
SRCS_KRL+=	krl.c

SRCS_PKT+=	canohost.c
SRCS_PKT+=	dispatch.c
SRCS_PKT+=	hmac.c
SRCS_PKT+=	kex.c
SRCS_PKT+=	mac.c
SRCS_PKT+=	packet.c
SRCS_PKT+=	umac.c
SRCS_PKT+=	umac128.c

SRCS_PROT+=	channels.c
SRCS_PROT+=	monitor_fdpass.c
SRCS_PROT+=	nchan.c
SRCS_PROT+=	ttymodes.c

SRCS_UTL+=	addrmatch.c
SRCS_UTL+=	match.c

.if (${OPENSSL:L} == "yes")
SRCS_PKCS11+=	ssh-pkcs11.c
.else
SRCS_PKCS11+=
.endif

WITH_XMSS?=	no
.if (${WITH_XMSS:L} == "yes")
CFLAGS+=	-DWITH_XMSS
SRCS_KEY+=	ssh-xmss.c
SRCS_KEY+=	sshkey-xmss.c
SRCS_KEY+=	xmss_commons.c
SRCS_KEY+=	xmss_fast.c
SRCS_KEY+=	xmss_hash.c
SRCS_KEY+=	xmss_hash_address.c
SRCS_KEY+=	xmss_wots.c
.endif

.include <bsd.obj.mk>
