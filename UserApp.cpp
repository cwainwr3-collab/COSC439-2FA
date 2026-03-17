
//This method will open a UDP socket and send a specified message (fix arguement for this later) and close once it has recieved a reply
int SendMessage()
{

}

//message to SA
typedef struct {

enum { registerOTPA,  acknowledgeRegister, login, responsePassword, responseNewKey, logout} messageType;                                   /* same size as an unsigned int */ 

unsigned int userID;                           /* user identifier */

unsigned int pubKeyOrEncPwd;        /* OTP public key or UA encrypted password */

}OPTAorUAtoSA;

/*  messageType = registerOTPA:
    Message sent from OTPA
    userID = corresponding user’s userID. 
    pubKeyOrEncPwd = 0 (not used)
    messageType = acknowledgeRegister:
    Message sent from an OTPA
    userID = corresponding user’s userID. 
    pubKeyOrEncPwd = 0 (not used)
    messageType = login:
    Message sent from a UA
    userID = corresponding user’s userID. 
    pubKeyOrEncPwd = 0 (not used)
    messageType = responsePassword:
    Message sent from a UA
    userID = corresponding user’s userID. 
    pubKeyOrEncPwd = encrypted password
    messageType = responseNewKey:
    Message sent from an OTPA
    userID = corresponding user’s userID. 
    pubKeyOrEncPwd = OTPA public key
    messageType = logout:
    Message sent from a UA
    userID = corresponding user’s userID. 
    pubKeyOrEncPwd = 0 (not used)
*/