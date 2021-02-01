/* Class: Instance
 * ----------
 * TIE-02201/TIE-02207 SPRING 2020
 * ----------
 * Class that represent a single instance.
 *
 * Note: Students should make changes to this class, and add their info and
 * specifics of the class to this comment.
 * */
#ifndef INSTANCE_HH
#define INSTANCE_HH

#include "account.hh"
#include "date.hh"
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

// Forward-declaration of Course, so that instance can point to the course it belongs to.
class Course;

const std::string ALREADY_REGISTERED = "Error: Student has already registered on this course.";
const std::string LATE = "Error: Can't sign up on instance after the starting date.";
const std::string INDENT = "    ";

class Instance
{
public:
    /**
     * @brief Instance
     * @param name
     * @param day
     */
    Instance(std::string name, const Date day);
    ~Instance();

    /**
     * @brief print_amount_of_students
     * Prints the amount of students signed up on the instance.
     */
    void print_amount_of_students();

    /**
     * @brief print_signups
     * Prints the account information of the students who have signed up on the instance.
     */
    void print_signups();

    /**
     * @brief add_signup
     * @param account
     * Adds a student as one of the instance's signups.
     */
    void add_signup(Account* account);

    /**
     * @brief print
     * Prints information about the instance.
     */
    void print_instance_info();

    /**
     * @brief is_named
     * @param name
     * @return true if the param name is the name of the instance. False if not.
     * Checks if the name given as the parameter is the name of the instance.
     */
    bool is_named(const std::string &name);

    /**
     * @brief is_signed_up
     * @param account
     * @return true if the param account is one of the students signed up on the instance. False if not.
     * Checks if the account given as the parameter is signed up on the instance.
     */
    bool is_signed_up(Account* account);

    /**
     * @brief get_name
     * @return name of the instance.
     */
    const std::string get_name();

    /**
     * @brief get_date
     * @return starting date of the intance.
     */
    const Date get_date();

private:

    // Name of the instance.
    std::string name_;

    // Starting date of the instance.
    const Date starting_date_;

    // Students who have signed up on the instance.
    std::vector<Account*> students_;


};

#endif // INSTANCE_HH
