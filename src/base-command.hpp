#ifndef H_INCLUDE_CLI_BASE_COMMAND
#define H_INCLUDE_CLI_BASE_COMMAND

#include "command.hpp"

class BaseCommand : public Commander::Command {
public:
  using Commander::Command::Command;

protected:

  BaseCommand *initialize_wrapper() {
    this->add("-h, --help", "Shows help.");
    this->Commander::Command::initialize_wrapper();
    return this;
  }

  int execute_wrapper(Commander::ArgumentList *list) const {
    if (this->get_option("--help")->has_appeared()) {
      std::cout << this->get_help() << std::endl;
      return 0;
    }
    return this->Command::execute_wrapper(list);
  }
};
#endif
