typedef struct {

enum { confirmRegister, requestNewKey  } messageType;                                  /* same as unsigned int */ 

unsigned int userID;                           /* user identifier*/

unsigned int publicKey;                      /* OTP public key */
} SAtoOTPA;

/*  messageType = confirmRegister
    userID = corresponding user’s userID. 
    publicKey = 0 (not used)
    messageType = requestNewKey
    userID = corresponding user’s userID. 
    publicKey = SA public key
*/

typedef struct {

enum { requestPassword,  confirmLogin  } messageType;          /* same size as an unsigned int */

unsigned int userID;                           /* user identifier */

enum { success, fail} status;                                 /* login status */        

} SAtoUA;

/*  messageType = requestPassword:
    userID = corresponding user’s userID. 
    status = (not used)
    messageType = confirmLogin:
    userID = corresponding user’s userID. 
    status = login status
*/