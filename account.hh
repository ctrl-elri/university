/* Class: Account
  * ----------
  * Defines a student or a staff account in the university system.
  *
  * In the project, this class should be expanded to
  * include study history of the account.
  * */
#ifndef ACCOUNT_HH
#define ACCOUNT_HH

#include "date.hh"
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>

class Instance;
class Course;

const std::string NO_SIGNUPS = "No signups found on this instance.";
const std::string SIGNED_UP = "Signed up on the course instance.";
const std::string COMPLETED = "Course completed.";

class Account
{
public:
    /**
     * @brief Account constructor
     * @param full_name as "frontname lastname"
     * @param email
     * @param account_number
     */
    Account(std::string full_name, std::string email, int account_number);

    /**
     * @brief print account info on one line
     */
    void print() const;

    /**
     * @brief add_instance
     * @param instance
     * Adds the instance as one of the instances currently being executed.
     */
    void add_instance(Instance* instance);

    /**
     * @brief complete_course
     * @param course
     * @param instance
     * Registeres the course and the instance as completed.
     * If the instance isn't on the list of currently executable instances,
     * notifies the user and doesn't carry out the command.
     */
    void complete_course(Course* course, Instance* instance);

    /**
     * @brief get_current_courses
     * @return the names of the instances currently being executed.
     */
    std::vector<std::string> get_current_instances();

    /**
     * @brief print_completed_courses
     * Prints information of the completed courses.
     */
    void print_completed_courses();

    /**
     * @brief get_email
     * @return email linked to this account
     */
    std::string get_email();

private:
    std::string full_name_;
    std::string last_name_;
    std::string first_name_;
    std::string email_;
    const int account_number_;
    std::vector<Instance*> current_;
    std::vector<Course*> completed_;
};

#endif // ACCOUNT_HH
