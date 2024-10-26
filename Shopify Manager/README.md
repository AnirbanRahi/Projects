# Shopify Manager

This **Shopify Manager** is a console-based application developed in C++. It is designed to help manage a shop's inventory, sales, billing, and staff information efficiently. The project was developed over a period of nearly two months as a comprehensive software solution for small to medium-sized shops.

## Table of Contents

- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [File Structure](#file-structure)
- [Customization](#customization)
- [Future Enhancements](#future-enhancements)
- [Contributing](#contributing)
- [License](#license)

## Features

- **User Authentication**: Different access levels for managers and staff for security.
- **Inventory Management**: Easily add, edit, delete, and view products in the shop's inventory.
- **Billing System**: Generate and print customer bills with calculated prices and taxes and save in csv file.
- **Staff Management**: Manage staff details, update roles, and maintain employee records.
- **Sales Records**: Generate and display sales records based on given criteria.


## Installation

### Prerequisites

- **C++ Compiler**: Requires the latest version of g++ for compilation.
- **CMake** (optional but recommended): Use CMake to manage the build configuration.

### Steps

#### 1. Clone the Repository
Clone the repository to your local machine.

```bash
git clone https://github.com/IT23043/shop-management-system.git
```

#### 2. Build the Project
Use CMake to build the project or compile manually with g++.

```bash
cd shop-management-system
mkdir build
cd build
cmake ..
make
```

#### 3. Run the Application
Execute the compiled program to start using the system.

## Usage

- **Admin Access**: Log in with the admin email and password to access full functionality.
- **Staff Access**: Use the manager email and password for staff functions.
- **Menu Navigation**: Follow on-screen options to navigate through features like managing inventory, billing, and reports.

## File Structure

The main files and folders are organized as follows:

shop-management-system/
├── src/                # Source code files
├── header/             # Header files
├── data/               # CSV files for inventory, staff, etc.
└── README.md           # Project documentation


## Customization

- **Email Credentials**:By default the admin and manager email and password is "admin". Update email configurations in the code to integrate email-based functionalities for staff and admin communications.
- **Inventory and Staff Data**: Modify the CSV files in the `data/` directory for initial shop data.

## Future Enhancements

1. **Graphical User Interface (GUI)**: Plan to integrate a Java Swing-based GUI for better user experience.
2. **Database Support**: Migrate from CSV files to a robust database for handling larger data sets.

## Contributing

Contributions are welcome! Please fork this repository, make your changes, and submit a pull request for review.

## License

This project is licensed under the MIT License. See `LICENSE` for details.
