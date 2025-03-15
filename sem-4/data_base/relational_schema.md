# Relational Schema

```scss
Patient(ssn, name, dob)
Primary Key ssn


Doctor(ssn, name, startdate)
Primary Key ssn


Specialist(ssn, specialization)
Primary Key ssn
    references Doctor(ssn)


generalPhysician(ssn, certification_date)
Primary Key ssn
    references Doctor(ssn)


Drug(trademark, formula)
Primary Key trademark

Prescirbes(doctor_ssn, patient_ssn, drug_trademark, pdate, quantity)
Foregin Key doctor_ssn
    references Doctor(ssn)
Foregin Key patient_ssn
    references Patient(ssn)
Foregin Key drug_trademark
    references Drug(trademark)


Pharmacy(phone, name, address, street, city)
Primary Key phone


PharmaCompany(name, phone [1..3])
Primary Key name


Sells(pharmacy_phone, drug_trademark)
Foregin Key pharmacy_phone
    referances Pharmacy(phone)
Foregin Key drug_trademark
    references Drug(trademark)


SoldBy(company_name, drug_trademark, id)
Primary Key id
Foreign Key company_name
    references PharmaCompany(name)
Foregin Key drug_trademark
    references Drug(trademark)


Contracts(company_name, pharmacy_phone, s_date, e_date, text)
Foregin Key comapny_name
    references PharmaCompany(name)
Foregin Key pharmacy_phone
    references Pharmacy(phone)


Employee(ssn, name)
Primary Key ssn


Works(employee_ssn, pharmacy_phone)
Foregin Key employee_ssn
    references Employee(ssn)
Foregin Key pharmacy_phone
    references Pharmacy(phone)


Supervisor(supervisor_ssn, s_date)
Primary Key supervisor_ssn
    references Employee(ssn)


Sees(patient_ssn, doctor_ssn)
Foregin Key patient_ssn
    references Patient(ssn)
Foregin Key doctor_ssn
    references Doctor(ssn)
```

# Database Code

```sql
CREATE DATABASE data_base_assignment_3;
USE data_base_assignment_3;

CREATE TABLE PharmaCompany (
    name VARCHAR(255) PRIMARY KEY NOT NULL,
    phone VARCHAR(10) NOT NULL
);

CREATE TABLE Pharmacy (
    phone VARCHAR(10) PRIMARY KEY NOT NULL,
    name VARCHAR(255) NOT NULL,
    address VARCHAR(255) NOT NULL,
    street VARCHAR(255) NOT NULL,
    city VARCHAR(255) NOT NULL
);

CREATE TABLE Drug (
    trademark VARCHAR(255) PRIMARY KEY NOT NULL,
    formula TEXT NOT NULL
);

CREATE TABLE Sells (
    pharmacy_phone VARCHAR(10) NOT NULL,
    drug_trademark VARCHAR(255) NOT NULL,
    FOREIGN KEY (pharmacy_phone) REFERENCES Pharmacy(phone) ON DELETE CASCADE,
    FOREIGN KEY (drug_trademark) REFERENCES Drug(trademark) ON DELETE CASCADE
);

CREATE TABLE SoldBy (
    id INT AUTO_INCREMENT PRIMARY KEY,
    company_name VARCHAR(255) NOT NULL,
    drug_trademark VARCHAR(255) NOT NULL,
    FOREIGN KEY (company_name) REFERENCES PharmaCompany(name) ON DELETE CASCADE,
    FOREIGN KEY (drug_trademark) REFERENCES Drug(trademark) ON DELETE CASCADE
);

CREATE TABLE Contracts (
    company_name VARCHAR(255) NOT NULL,
    pharmacy_phone VARCHAR(255) NOT NULL,
    s_date DATE NOT NULL,
    e_date DATE,
    text TEXT NOT NULL,
    FOREIGN KEY (company_name) REFERENCES PharmaCompany(name) ON DELETE CASCADE,
    FOREIGN KEY (pharmacy_phone) REFERENCES Pharmacy(phone) ON DELETE CASCADE
);
```
