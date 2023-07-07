#pragma once
#include <iostream>
#include <mysql.h>


/**
 * The Singleton class defines the `GetInstance` method that serves as an
 * alternative to constructor and lets clients access the same instance of this
 * class over and over.
 */
class MySQLORM {

    /**
     * The Singleton's constructor should always be private to prevent direct
     * construction calls with the `new` operator.
     */

protected:
    MySQLORM()
    {
        connect = mysql_init(0);
        connect = mysql_real_connect(connect, "sq8.freesse.com", "s850", "ienbQ", "7850", 3306, NULL, 0);
    }

    static MySQLORM* singleton_;

    MYSQL* connect;

public:

    /**
     * Singletons should not be cloneable.
     */
    MySQLORM(MySQLORM& other) = delete;
    /**
     * Singletons should not be assignable.
     */
    void operator=(const MySQLORM&) = delete;
    /**
     * This is the static method that controls the access to the singleton
     * instance. On the first run, it creates a singleton object and places it
     * into the static field. On subsequent runs, it returns the client existing
     * object stored in the static field.
     */

    static MySQLORM* GetInstance();

    MYSQL* conn() const {

        return connect;
    }
};

MySQLORM* MySQLORM::singleton_ = nullptr;;

/**
 * Static methods should be defined outside the class.
 */
MySQLORM* MySQLORM::GetInstance()
{
    /**
     * This is a safer way to create an instance. instance = new Singleton is
     * dangeruous in case two instance threads wants to access at the same time
     */
    if (singleton_ == nullptr) {
        singleton_ = new MySQLORM();
    }
    return singleton_;
}
