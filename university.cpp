#include "university.hh"

University::University():running_number_(111111)
{
}

University::~University()
{
    for ( auto course : courses_ ){
        delete course.second;
    }

    for ( auto account : accounts_ ){
        delete account.second;
    }

}

void University::add_course(Params params)
{
    if ( courses_.find(params.at(0)) != courses_.end() ){
        std::cout << ALREADY_EXISTS << std::endl;
        return;
    } else {
        std::cout << NEW_COURSE << std::endl;
    }

    Course* n_course = new Course(params.at(0), params.at(1));
    courses_.insert({n_course->get_code(), n_course});
}

void University::print_courses(Params)
{
    for ( auto course : courses_ ){
        course.second->print_info(true);
    }
}

void University::print_course(Params params)
{
    if ( courses_.find(params.at(0)) == courses_.end() ){
        std::cout << CANT_FIND << params.at(0) << std::endl;
        return;
    }

    courses_.at(params.at(0))->print_long_info();
}

void University::add_account(Params params)
{
    for( std::map<int, Account*>::iterator iter = accounts_.begin(); iter != accounts_.end(); ++iter ) {
        if( iter->second->get_email() == params.at(1) ) {
            std::cout << ALREADY_EXISTS << std::endl;
            return;
        }
    }

    int account_number = running_number_++;
    Account* n_account = new Account(params.at(0), params.at(1), account_number);
    accounts_.insert({account_number, n_account});
    std::cout << NEW_ACCOUNT << std::endl;
    n_account->print();
}

void University::print_accounts(Params)
{
    for ( auto account : accounts_ ){
        account.second->print();
    }
}

void University::print_account_info(Params params)
{
    std::map<int, Account*>::iterator iter = accounts_.find(std::stoi(params.at(0)));
    if ( iter == accounts_.end() ){
        std::cout << CANT_FIND << params.at(0) << std::endl;
        return;
    }
    iter->second->print();
}

void University::add_staff_to_course(Params params)
{
    if ( courses_.find(params.at(0)) == courses_.end() ){
        std::cout << CANT_FIND << params.at(0) << std::endl;
        return;
    }
    if ( accounts_.find(std::stoi(params.at(1))) == accounts_.end() ){
        std::cout << CANT_FIND << params.at(1) << std::endl;
        return;
    }

    courses_.at(params.at(0))->add_staff(accounts_.at(std::stoi(params.at(1))));
}


void University::add_instance(Params params)
{
    // Checks that the course exists and
    // that the course doesn't already have the instance.
    if (!is_course(params.at(0))){
        return;
    }
    if (courses_.at(params.at(0))->has_instance(params.at(1))){
        std::cout << INSTANCE_EXISTS << std::endl;
        return;
    }

    // A new instance object is created and the current date is set as the starting date.
    // The instance is saved as one of the course's intances.
    const Date starting_date = utils::today;
    Instance* n_instance= new Instance(params.at(1), starting_date);
    courses_.at(params.at(0))->new_instance(n_instance);
}

void University::sign_up_on_course(Params params)
{
    // Checks that the course exists and that the course has the instance.
    if (!is_course(params.at(0))){
        return;
    }
    else if (!courses_.at(params.at(0))->has_instance(params.at(1))){
        std::cout << CANT_FIND << params.at(1) << std::endl;
        return;

    } else if (!is_account(stoi(params.at(2)))){
        return;
    }

    // Checks that the account hasn't already signed up on the instance and
    // that the instance's starting date hasn't already passed making the signup too late.
    Instance* instance = courses_.at(params.at(0))->get_instance(params.at(1));
    if (instance->is_signed_up(accounts_.at(stoi(params.at(2))))){
        return;
    }
    else if (!utils::today.operator <(instance->get_date()) && !utils::today.operator ==(instance->get_date())){
        std::cout << LATE << std::endl;
        return;
    }

    // Signup is registered in the instance- and account -objects.
    instance->add_signup(accounts_.at(stoi(params.at(2))));
    accounts_.at(stoi(params.at(2)))->add_instance(instance);

}


void University::complete_course(Params params)
{
    // Checks that the course and account exist.
    if (!is_course(params.at(0))){
        return;
    }
    else if (!is_account(stoi(params.at(2)))){
        return;
    }

    // Account -object registers the course as completed.
    accounts_.at(stoi(params.at(2)))->complete_course(courses_.at(params.at(0)), courses_.at(params.at(0))->get_instance(params.at(1)));
}


void University::print_signups(Params params)
{
    if (!is_course(params.at(0))){
        return;
    }

    for (auto course: courses_){
        if (course.first == params.at(0)){
            course.second->print_signups();
        }
    }
}

void University::print_study_state(Params params)
{
    if (!is_account(stoi(params.at(0)))){
        return;
    }

    std::cout << "Current:" << std::endl;
    std::vector<std::string> current_courses = accounts_.at(stoi(params.at(0)))->get_current_instances();
    for (auto current_instance: current_courses){
        for (auto course: courses_){
            if(course.second->has_instance(current_instance)){
                course.second->print_info(false);
                std::cout << " " << current_instance << std::endl;
            }
        }
    }

    std::cout << "Completed:" << std::endl;
    accounts_.at(stoi(params.at(0)))->print_completed_courses();
}

void University::print_completed(Params params)
{
    if (!is_account(stoi(params.at(0)))){
        return;
    }
    accounts_.at(stoi(params.at(0)))->print_completed_courses();
}

void University::set_date(Params params)
{
    utils::today = Date(std::stoi(params.at(0)), std::stoi(params.at(1)), std::stoi(params.at(2)));
    std::cout << "Date has been set to ";
    utils::today.print();
    std::cout << std::endl;
}

void University::advance_date(Params params)
{
    utils::today.advance_by(std::stoi(params.at(0)));
    std::cout << "New date is ";
    utils::today.print();
    std::cout << std::endl;
}

void University::advance_by_period(Params)
{
    utils::today.advance_by_period_length();
    std::cout << "New date is ";
    utils::today.print();
    std::cout << std::endl;
}

bool University::is_course(std::string course_name)
{
    if (courses_.find(course_name) == courses_.end()){
        std::cout << CANT_FIND << course_name << std::endl;
        return false;
    }

    return true;
}

bool University::is_account(int account_number)
{
    if (accounts_.find(account_number) == accounts_.end()){
        std::cout << CANT_FIND << account_number << std::endl;
        return false;
    }

    return true;
}
