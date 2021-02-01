#include "instance.hh"
#include "course.hh"

Instance::Instance(std::string name, const Date starting_date):
    name_(name), starting_date_(starting_date)
{

}

Instance::~Instance()
{

}

void Instance::print_amount_of_students()
{
    std::cout << "    Amount of students: " << students_.size() << std::endl;

}



void Instance::print_signups()
{
    for (auto student: students_){
        std::cout << "    ";
        student->print();
    }
}

void Instance::add_signup(Account* account)
{
    students_.push_back(account);
}

void Instance::print_instance_info()
{
    std::cout << name_ << std::endl;
    std::cout << "    Starting date: ";
    starting_date_.print();
    std::cout << "\n";
}

bool Instance::is_named(const std::string &name)
{
    if (name_ == name){
        return true;
    }
    return false;
}

bool Instance::is_signed_up(Account* account)
{
    for (auto student: students_){
        if (account == student){
            std::cout << ALREADY_REGISTERED << std::endl;
            return true;
        }
    }

    return false;
}

const std::string Instance::get_name()
{
    return name_;
}


const Date Instance::get_date()
{
    return starting_date_;
}


