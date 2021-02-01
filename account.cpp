#include "account.hh"
#include "utils.hh"
#include "instance.hh"
#include "course.hh"

Account::Account(std::string full_name, std::string email, int account_number):
    full_name_(full_name),
    last_name_(""),
    first_name_(""),
    email_(email),
    account_number_(account_number)
{
    std::vector<std::string> name = utils::split(full_name_, ' ');
    last_name_ = name.back();
    first_name_ = name.front();
}


void Account::print() const
{
    std::cout << account_number_ << ": "
              << first_name_ << " "
              << last_name_  << ", "
              << email_ << std::endl;
}

void Account::add_instance(Instance* instance)
{
    current_.push_back(instance);
    std::cout << SIGNED_UP << std::endl;
}

void Account::complete_course(Course* course, Instance* instance)
{

    if (std::find(current_.begin(), current_.end(), instance) == current_.end()){
        std::cout << NO_SIGNUPS << std::endl;
        return;
    }

    // Instance is removed from the list of instances currently being executed and
    // the course is added to the list of completed courses.
    for (std::vector<Instance*>::iterator it = current_.begin(); it < current_.end(); ++it){
        if (*it == instance){
           current_.erase(it);
        }
    }
    completed_.push_back(course);
    std::cout << COMPLETED << std::endl;
}

std::vector<std::string> Account::get_current_instances()
{
    std::vector<std::string> current_instances;
    for (auto current_instance: current_){
        current_instances.push_back(current_instance->get_name());
    }

    return current_instances;
}



void Account::print_completed_courses()
{
    if (completed_.size()==0){
        std::cout << "Total credits: 0"  << std::endl;
        return;
    }

    // Sum of the total credits acquired from completed courses.
    int total_credits = 0;
    for (auto completed_course: completed_){
        completed_course->print_info(true);
        total_credits += completed_course->get_credits();
    }

    std::cout << "Total credits: " << total_credits << std::endl;

}

std::string Account::get_email()
{
    return email_;
}
