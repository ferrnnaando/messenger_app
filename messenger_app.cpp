#include "header.h"

int main() {
    MYSQL_ROW fila;
    MYSQL_RES* resultado;
    MYSQL* connect;

    //VALIDATE CONEXION///////////////
    //MySQLORM* mysql = MySQLORM::GetInstance();
    //MYSQL* connect = mysql->conn();

    std::string windows_user;
    windows_user = GetUserName(infoBuf, &bufCharCount);
    std::cout << credits;;
    std::cout << "[!] Comprobando version actual.. (" << version << ")";
    mysql_query(connect, std::string("SELECT * FROM version_historial WHERE version = '" + version + "' AND latest = 'yes';").c_str());
    resultado = mysql_store_result(connect);
    if (resultado->row_count == 0) {
        std::cout << "\n[!] Esta version ha quedado obsoleta, descarga la mas reciente.\n[!] El programa se cerrara en breves.\n";
        Sleep(3000);
        exit(-1);

    }
    else {
        std::cout << "\n[!] Te encuentras con una version del programa actualizada.";
        Sleep(3000);
     
        mysql_query(connect, std::string("SELECT * FROM users_details WHERE windows_user = '" + windows_user + "';").c_str());
        resultado = mysql_store_result(connect);
        if (resultado->row_count == 0) {
            mysql_query(connect, std::string("INSERT INTO users_details(windows_user) VALUES('" + windows_user + "';").c_str());
        } else {
            std::cout << "[!] Informacion ya registrada en el sistema.";
            Sleep(3000);
        }

        system("cls");
    }




    if (connect) {
        system("cls");
        std::cout << "[!] Conexion exitosa.";
    init:
        system("cls");
        std::cout << credits;;
        std::cout << "(1) - Iniciar sesion\n(2) - Registrarme\n(3) - Configuracion\n(4) - Informacion / Acerca de\n \n> ";
        std::cin >> whattodo;




        //SWITCH CASE//
        switch (whattodo) {
            //LOGIN MENU
        case 1:
            while (loginAttempt < 3) {
                login:
                system("cls");
                std::cout << credits;;
                std::cout << "[?] Nombre de usuario: ";
                std::cin >> username_log;
                std::cout << "[?] Introduce la contrasena: ";
                std::cin >> password_log;
              /*  ch = _getch();
                while (ch != 13) {
                    password_log.push_back(ch);
                    std::cout << "*";
                    ch = _getch();
                }*/

                
                std::string check_credentials = "SELECT * FROM users WHERE name = '" + username_log + "' AND password = '" + password_log + "';";
                const char* check_username_login = check_credentials.c_str();
                query_check = mysql_query(connect, check_username_login);
                if (!query_check) {
                    resultado = mysql_store_result(connect);
                    fila = mysql_fetch_row(resultado);
                    if (fila != NULL) {
                        system("cls");
                        std::cout << credits;;
                        std::cout << "[!] Iniciando sesion...";
                        Sleep(3000);
                        break;
                    }
                    else {
                        loginAttempt++;
                        std::cout << "\n\n[!] Las credenciales introducidas son incorrectas. (" << loginAttempt << "/3)";
                        Sleep(1000);
                    }
                }
            }

            if (loginAttempt++ == 3) {
                std::cout << "\n[!] Has fallado muchas veces. El programa se cerrara en breves.";
                Sleep(3000);
                exit(-1);
            }

            if (loginAttempt++ == 3) {
                std::cout << "\n[!] Has fallado muchas veces. El programa se cerrara en breves.";
                Sleep(3000);
                exit(-1);
            }

            std::cout << "\n[!] Bienvenido.";
            while (true) {
                system("cls");
                std::string chat_show = "SELECT * FROM chat";
                const char* show_chat = chat_show.c_str();
                mysql_query(connect, show_chat);

                resultado = mysql_store_result(connect);
                while (fila = mysql_fetch_row(resultado)) {
                    std::cout << "[" << fila[0] << "] - " << fila[3] << " - " << fila[1] << ": " << fila[2] << "\n";
                }
                Sleep(1000);
            }

            /*std::cout << "\n\n> ";
            std::cin >> message_send;
            std::string send_message = "INSERT INTO chat(name, message) VALUES('" + username_log + "', '" + message_send + "')";
            const char* message = send_message.c_str();
            mysql_query(connect, message);*/
            break;









        case 2:
        reg:
            if (loginAttempt++ == 5) {
                std::cout << "\n[!] Has fallado muchas veces. El programa se cerrara en breves.";
                Sleep(3000);
                exit(-1);
            }
            system("cls");
            std::cout << credits;;
            std::cout << "[?] Nombre de usuario: ";
            std::cin >> username_reg;
            std::cout << "[?] Introduce un correo electronico: ";
            std::cin >> gmail_reg;

            std::cout << "[?] Introduce una contrasena: ";
            ch = _getch();
            while (ch != 13) {
                password_reg.push_back(ch);
                std::cout << "*";
                ch = _getch();
            }

            std::cout << "\n\n[!] Registrando...";

            if (check_mail(gmail_reg) == 1) {
                loginAttempt++;
                std::cout << "\n[!] El correo introducido no es valido, vuelve a intentarlo. (" << loginAttempt << "/5)";
                Sleep(1000);
                goto reg;
            }
            else {
                mysql_query(connect, check_exists_register);
                resultado = mysql_store_result(connect);
                if (resultado->row_count == 0) {
                    loginAttempt++;
                    std::cout << "\n[!] El nombre de usuario introducido ya existe, prueba con otro. (" << loginAttempt << "/5)";
                    goto reg;
                }
                else {
                    query_consult = mysql_query(connect, register_user);
                    if (query_consult) {
                        system("cls");
                        std::cout << credits;;
                        std::cout << "[!] Usuario registrado correctamente. Por favor, inicie sesion.";
                        Sleep(3000);
                        goto init;
                    }
                    else {
                        system("cls");
                        std::cout << credits;;
                        std::cout << "[!] Usuario no registrado, vuelve a intentarlo.";
                        Sleep(3000);
                    }
                }
            }
            break;










        case 3:
        config:
            system("cls");
            std::cout << credits;;

            std::cout << "[!] Ajustes: \n\n" << f1_keyColorSwitch << " Color: " << color << "    Version : " << version << "    (F2) Idioma: " << idioma;
            std::cout << "\n\nPulsa (ESC) para salir.\n[!] Si inicias sesion tus preferencias de configuracion se guardaran, de lo contrario seran olvidadas.\n[!] Posiblemente no se guarde correctamente la informacion a la primera, asegurate pulsando varias veces la misma tecla.";
            system("pause");

            if (keyState = GetAsyncKeyState(VK_F1) & 0x8000) {
                if (f1_keyColorSwitch == "(F1)") {
                    f1_keyColorSwitch = "(F2 - F5)";
                f1:
                    if (GetAsyncKeyState(VK_F2) & 0x8000) { //F1
                        SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
                        color = "Rojo";
                        goto f1;
                    }
                    else if (GetAsyncKeyState(VK_F3) & 0x8000) { //f2
                        SetConsoleTextAttribute(h, FOREGROUND_INTENSITY | FOREGROUND_INTENSITY);
                        color = "Gris oscuro";
                        goto f1;
                    }
                    else if (GetAsyncKeyState(VK_F4) & 0x8000) { //virtual key &f3
                        SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                        color = "Verde";
                        goto f1;
                    }
                    else if (GetAsyncKeyState(VK_F5) & 0x8000) { //f4
                        SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                        color = "Azul";
                        goto f1;
                    }
                    else {
                        f1_keyColorSwitch == "(F1)";
                        goto config;
                    }
                }
                else {
                    f1_keyColorSwitch = "(F1)";
                }

                goto  config;

            } else if (keyState = GetAsyncKeyState(VK_F2) & 0x8000) {
                if (idioma == "Ingles") {
                    idioma = "Español";
                } else {
                    idioma = "Ingles";
                }
                goto config;
            } else if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
                goto init;
            } else {
                goto config;
            }

            break;








        case 4:
            aboutus:
            system("cls");
            std::cout << credits;
            std::cout << "DARKCHAT \n";
            system("pause");
            if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) { //ESC
                goto init;
            } else {
                goto aboutus;
            }

            break;




        default:
            system("cls");
            std::cout << credits;
            std::cout << "[!] Respuesta incorrecta, elige una opcion entre 1 y 2.";
            goto init;
        }
    }
    else {
    system("cls");
    std::cout << credits;;
    std::cout << "[!] Conexion denegada.";
    }
    
    return 0;
}