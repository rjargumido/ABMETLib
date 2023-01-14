#ifndef ABMETLIB_h
#define ABMETLIB_h

// File System
#define dir_user    "users/"
#define dir_admin   "admin/"
#define dir_borrow  "borrow/"
#define fn_user     "user_"
#define fn_admin    "admin_"
#define fn_borrow   "borrow_"

enum DataToSave {
    CONFIG_DATA,
    USER_DATA,
    ADMIN_DATA,
    TRANSACTION_DATA
};

class ABMET {
    public:

    private:
};

extern ABMET abmet;
#endif