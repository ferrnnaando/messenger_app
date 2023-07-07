#pragma once
#include "header.h"
#include "mysqlclass.h"

//version variable
std::string version = "2.3";

//queries
int query_check, query_consult, query_showchat, query_sendmessage, whattodo;
int query_user;

//user register information required
std::string username_reg, gmail_reg, password_reg;
char ch;

//user credentials info required
#define INFO_BUFFER_SIZE 32767
TCHAR  infoBuf[INFO_BUFFER_SIZE];
DWORD  bufCharCount = INFO_BUFFER_SIZE;
std::string windows_user;

//login variables
std::string username_log, password_log;
int loginAttempt = 0;
std::string message_send;

//mysql queries
const char* query_check_version = std::string("SELECT 1 FROM version_historial WHERE version = '" + version + "' AND latest = 'yes' LIMIT 1").c_str();
const char* check_exists_register = std::string("SELECT 1 FROM users WHERE name = '" + username_reg + "' LIMIT 1").c_str();
const char* register_user = std::string("INSERT INTO users(name, password, gmail) VALUES('" + username_reg + "', '" + password_reg + "', '" + gmail_reg + "')").c_str();

//credits variables
std::string credits = "\n DARKCHAT | void* proyect \n\n";

//setings variables
const char* chatcolor;
std::string color = "Gris claro";
std::string f1_keyColorSwitch = "(F1)";
std::string idioma = "Español";
bool toggleIdioma;
SHORT keyState; //tipo de variable requerida para usar el operador de asignacion y comparacion con al funcion GetAsyncKeyState
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);


bool check_mail(std::string& gmail_reg) {
    bool found_at = 0;
    size_t at_idx = 0;

    size_t dot_n = 0;
    size_t dot_idx = 0;
    size_t dot2_idx = 0;

    // return value
    bool is_invalid = false;

    constexpr size_t min_mail_size = 6; // x@x.xx

    // first initial size check
    is_invalid = gmail_reg.size() < min_mail_size;

    // search for '@' and '.' instances
    for (size_t i = 0; !is_invalid && i < gmail_reg.size(); i++) {
        if (gmail_reg.at(i) == '@') {
            if (found_at) {
                is_invalid = true;
                break;
            }
            at_idx = i;
            found_at = true;
        }
        else if (gmail_reg.at(i) == '.') {
            if (++dot_n == 1)
                dot_idx = i; // x@x.xx
            else if (dot_n == 2)
                dot2_idx = i; // x@x.xx.xx
            else {
                is_invalid = true;
                break;
            }
        }
    }

    // extra validity checks
    if (!is_invalid) {
        // @x.xx
        is_invalid = is_invalid || at_idx == 0;
        // x@.xx
        is_invalid = is_invalid || gmail_reg.at(at_idx + 1) == '.';
        // x@x.x
        is_invalid = is_invalid || dot_idx + 2 >= gmail_reg.size();

        // x@x..xx
        is_invalid = is_invalid || gmail_reg.at(dot_idx + 1) == '.';
        // x@x.xx.x
        is_invalid = is_invalid || dot2_idx + 2 >= gmail_reg.size();
    }

    return is_invalid;
}