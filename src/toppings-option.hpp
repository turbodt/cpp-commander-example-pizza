#ifndef H_INCLUDE_CLI_TOPPINGS_OPTION
#define H_INCLUDE_CLI_TOPPINGS_OPTION

#include "command.hpp"

/**
 * Advanced usage: override an option
 */

class ToppingsOption : public Commander::Option {
public:
  using Commander::Option::Option;

  virtual std::string get_label() const override {
    std::cerr << "HERE" << std::endl;
    return this->Commander::Option::get_label() + " N t1 ... t_N";
  };

  void assert_not_finished_list(Commander::ArgumentList const *list) const {
    if (list->is_finished()) {
      throw Commander::OptionParsingException("Not enough arguments.");
    }
  };

  ToppingsOption *parse_argument_list(Commander::ArgumentList *list) override {
    this->assert_not_finished_list(list);

    // check this is the correct argument
    if (!this->has_name(list->get_current())) {
      throw Commander::OptionParsingException("Names do not match.");
    }
    list->next();

    // get the number of toppings
    this->assert_not_finished_list(list);
    int n = std::stoi(list->get_current());
    this->get_values()->clear();
    list->next();

    // create a positional argument for each topping
    for (int i = 0; i < n; i++) {
      this->assert_not_finished_list(list);

      // create positional argument
      auto positional_argument =
          Commander::PositionalArgument("t" + std::to_string(i));
      positional_argument.set_optional(false);

      // set the corresponding value
      positional_argument.set_value(list->get_current());

      // push the positional argument to the value array
      this->get_values()->push_back(positional_argument);

      list->next();
    }

    this->has_been_parsed = true;
    return this;
  };
};

#endif
