#include "./base-command.hpp"
#include "./toppings-option.hpp"
#include "./utils.hpp"
#include <set>
#include <stdexcept>
#include <string>
#include <vector>

class OrderCommand : public BaseCommand {
protected:
  ToppingsOption toppings_opt = ToppingsOption(
      "-t, --toppings", "Adds a list of toppings on your pizza.");
  ;

  std::set<std::string> allowed_flavours = {"Margherita", "Bbq", "Hawaiian"};
  std::set<std::string> allowed_sizes = {"small", "medium", "large"};

public:
  using BaseCommand::BaseCommand;

  /**
   * Basic usage: override initialize and execute:
   */

  /**
   *  void initialize()
   *
   *  Here we define the properties of the command.
   */
  void initialize() {
    this->set_description("This command creates a new order.")
        ->add("-q, --quantity <quantity>", "How many units. Default = 1.")
        ->add("--lactose-free", "Set this option to get a lactose-free pizza.")
        ->add_option(&this->toppings_opt)
        ->add("<flavour>", "Flavour of the pizza. One of:\n"
                           "  - Margherita: A classic.\n"
                           "  - Hawaiian: With pineapple.\n"
                           "  - Bbq: Delicious!")
        ->add("[size]", "Three sizes: small, medium, large.");
  }

  /**
   *  int execute() const
   *
   *  Here we define what the command has to do.
   */
  int execute() const {
    auto flavour = this->get_flavour();
    auto size = this->get_size();
    auto quantity = this->get_quantity();
    auto toppings = this->get_toppings();

    std::cout << flavour << " pizza successfully ordered!" << std::endl;
    std::cout << "  - Size: " << size << std::endl;
    std::cout << "  - Quantity: " << quantity << std::endl;

    // Location option (From parent command)
    auto location_opt = this->get_global_option("-l");
    if (location_opt->has_appeared()) {
      std::string location_str = location_opt->get_value(0)->get_value();
      std::cout << "  - From: " << location_str << std::endl;
    }

    if (!toppings.size()) {
      std::cout << "  - No toppings." << std::endl;
    } else {
      std::cout << "  - Toppings (" << toppings.size() << "):" << std::endl;
      for (auto topping : toppings) {
        std::cout << "    + " << topping << std::endl;
      }
    }

    if (this->is_lactose_free()) {
      std::cout << "\nIn addition, you requested your order to be lactose-free."
                << "\nFortunatelly, this is an example and no real life, so we"
                << " can provide you a lactose-free pizza :)." << std::endl;
    }

    return 0;
  };

  /**
   * helper parsers
   */

  std::string get_flavour() const {
    auto arg = this->get_positional("flavour");
    std::string raw_flavour = arg->get_value();
    std::string flavour = capitalize(raw_flavour);
    if (!this->allowed_flavours.count(flavour)) {
      throw std::invalid_argument("Invalid pizza flavour \"" + raw_flavour +
                                  "\".");
    }
    return flavour;
  }

  std::string get_size() const {
    auto arg = this->get_positional("size");
    if (!arg->has_value()) {
      return "medium";
    }

    std::string raw_size = arg->get_value();
    std::string size = raw_size;
    if (!this->allowed_sizes.count(size)) {
      throw std::invalid_argument("Invalid pizza size \"" + raw_size + "\".");
    }
    return size;
  }

  int get_quantity() const {
    auto opt = this->get_option("--quantity");
    if (!opt->has_appeared()) {
      return 1;
    }
    return std::stoi(opt->get_value(0)->get_value());
  }

  bool is_lactose_free() const {
    return this->get_option("--lactose-free")->has_appeared();
  }

  std::vector<std::string> get_toppings() const {
    int num_toppings = this->toppings_opt.get_values()->size();
    std::vector<std::string> toppings(num_toppings);
    for (int i = 0; i < num_toppings; i++) {
      auto pos_arg = this->toppings_opt.get_value(i);
      toppings[i] = pos_arg->get_value();
    }
    return toppings;
  }
};
