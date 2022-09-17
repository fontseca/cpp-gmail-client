#include <iostream>
#include <sstream>

#include "SMTPClient.h"

auto lambda_logger = [](const std::string &str)
{
  std::cout << str;
  return;
};

auto main() -> int32_t
{
  CSMTPClient SMTPClient(lambda_logger);
  const std::string email_provider{"smtps://smtp.gmail.com:465"};
  // TODO: Use POO instead of variables
  std::string sender_email;
  std::string sender_name;
  std::string sender_password;
  std::string recipient_email;
  std::string recipient_name;
  std::string sender_subject;
  std::stringstream ss;

  std::cout << "Super-Simple C++ Gmail client." << std::endl;
  std::cout << "Author: Jeremy Fonseca (https://github.com/fontseca/super-simple-gmail-client)" << std::endl;
  std::cout << "(To work correctly you will possibly need an App Password)\n\n";

  std::cout << "Sender name: ";
  std::getline(std::cin, sender_name);

  std::cout << "Sender email: ";
  std::getline(std::cin, sender_email);

  std::cout << "Sender password: ";
  std::getline(std::cin, sender_password);

  std::cout << "Recipient email: ";
  std::getline(std::cin, recipient_email);

  std::cout << "Recipient name: ";
  std::getline(std::cin, recipient_name);

  std::cout << "Subject: ";
  std::getline(std::cin, sender_subject);

  std::cout << "\nStarting session...";

  const bool session_started = SMTPClient.InitSession(email_provider, sender_email, sender_password, CMailClient::SettingsFlag::ALL_FLAGS, CMailClient::SslTlsFlag::ENABLE_SSL);

  std::cout << " Done." << std::endl;
  std::cout << "\nSeding email...";

  ss << "From: "
     << sender_name << " <" << sender_email << ">" << std::endl
     << "To: " << recipient_name << " <" << recipient_email << ">" << std::endl
     << "Subject: " << sender_subject << std::endl
     << std::endl
     << sender_subject << std::endl;

  const bool sending_status = SMTPClient.SendString(sender_email, recipient_email, "", ss.str());

  if (!sending_status)
    std::cerr << "\nError: Email was not sent." << std::endl;
  else
    std::cout << " Sent." << std::endl;

  SMTPClient.CleanupSession();
  return EXIT_SUCCESS;
}
