$NetBSD: patch-scp.c,v 1.1 2013/05/01 19:58:26 imil Exp $

Interix support

--- scp.c.orig	2013-03-20 01:55:15.000000000 +0000
+++ scp.c
@@ -477,7 +477,11 @@ main(int argc, char **argv)
 	argc -= optind;
 	argv += optind;
 
+#ifdef HAVE_INTERIX
+	if ((pwd = getpwuid_ex(userid = getuid(), PW_FULLNAME)) == NULL)
+#else
 	if ((pwd = getpwuid(userid = getuid())) == NULL)
+#endif
 		fatal("unknown user %u", (u_int) userid);
 
 	if (!isatty(STDOUT_FILENO))
@@ -881,8 +885,10 @@ rsource(char *name, struct stat *statp)
 		return;
 	}
 	while ((dp = readdir(dirp)) != NULL) {
+#ifndef HAVE_INTERIX
 		if (dp->d_ino == 0)
 			continue;
+#endif
 		if (!strcmp(dp->d_name, ".") || !strcmp(dp->d_name, ".."))
 			continue;
 		if (strlen(name) + 1 + strlen(dp->d_name) >= sizeof(path) - 1) {
@@ -1279,7 +1285,9 @@ okname(char *cp0)
 			case '\'':
 			case '"':
 			case '`':
+#ifndef HAVE_INTERIX
 			case ' ':
+#endif
 			case '#':
 				goto bad;
 			default:
