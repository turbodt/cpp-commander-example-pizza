#include "./base-command.hpp"
#include "./order.cpp"
#include <iostream>

class MainCommand : public BaseCommand {
public:
  using BaseCommand::BaseCommand;

  void initialize() {
    this->set_description("A tool to manage orders on our pizza place!")
        ->add("-l,--location <store>",
              "Perform operation on that specific store."
              "\nOtherwise, the operation will be performed on the closer one.")
        ->add_subcommand("order", new OrderCommand());
  }
};

int main(int argc, char *argv[]) {
  auto command = MainCommand();
  return command.from_main(argc, argv);
}
