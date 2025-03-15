# Relational Schema

```cpp
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


Sells(pharmacy_phone, drug_trademark, company_name)
Foregin Key company_name
    references PharmaCompany(name)
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
CREATE DATABASE data_base_assignment;
USE data_base_assignment;

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
    company_name VARCHAR(255) NOT NULL,
    pharmacy_phone VARCHAR(10) NOT NULL,
    drug_trademark VARCHAR(255) NOT NULL,
    FOREIGN KEY (company_name) REFERENCES PharmaCompany(name) ON DELETE CASCADE,
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
    s_date DATE,
    e_date DATE,
    text TEXT,
    FOREIGN KEY (company_name) REFERENCES PharmaCompany(name) ON DELETE CASCADE,
    FOREIGN KEY (pharmacy_phone) REFERENCES Pharmacy(phone) ON DELETE CASCADE
);
```

```sql
INSERT INTO pharmacy (phone, name, address, street, city)
VALUES
    ('54327612', 'City Drug', '36 South Cherry', 'Starkville', 'MS 39759'),
    ('87435217', 'Pill Pack', '29 E. Pine Lane', 'Stuart', 'FL 34997'),
    ('98463251', 'Better Life', '8004 Eagle St.', 'Sarasota', 'FL 34231'),
    ('45362819', 'Pharma Best', '15 Williams Drive', 'Elgin', 'IL 60120'),
    ('87340213', 'Be Well', '790 Clay Road', 'Ooltewah', 'TN 37363'),
    ('35446281', 'Absolute Care', '39 Spruce Drive', 'Charlottesville', 'VA 22901');

INSERT INTO drug (trademark, formula)
VALUES
    ('Ultran', 'tramadol'),
    ('Advil', 'ibuprofen'),
    ('Aleve', 'naproxen'),
    ('Bayer Aspirin', 'aspirin'),
    ('Zipsor', 'diclofenac'),
    ('Irenka', 'duloxetine'),
    ('Myoflex', 'Trolamine salicylate');

INSERT INTO pharmacompany (name, phone)
VALUES
('Janson & Janson', '23749912'),
    ('Pfizer', '45732810'),
    ('Bayer', '88374291'),
    ('Roche', '66372910'),
    ('Abbott', '66392014'),
    ('Allergan', '47639201'),
    ('CSL', '84192200'),
    ('Vertex Pharmaceuticals', '91228345');

INSERT INTO contracts (company_name, pharmacy_phone)
VALUES
('Janson & Janson', '54327612'),
('Janson & Janson', '54327612'),
('Pfizer', '54327612'),
('Bayer', '87340213'),
('Roche', '35446281'),
('CSL', '98463251'),
('Abbott', '87340213'),
('Vertex Pharmaceuticals', '87340213'),
('Allergan', '98463251'),
('Allergan', '35446281');
    
INSERT INTO soldby (company_name, drug_trademark)
VALUES
('anson & Janson', 'Ultram'),
('Janson & Janson', 'Aleve'),
('Janson & Janson', 'Zipsor'),
('Janson & Janson', 'Myoflex'),
('Pfizer', 'Ultram'),
('Pfizer', 'Zipsor'),
('Bayer', 'Bayer Aspirin'),
('Roche', 'Irenka'),
('CSL', 'Ultram'),
('Abbott', 'Aleve'),
('Vertex Pharmaceuticals', 'Irenka'),
('Allergan', 'Advil');
    
INSERT INTO sells (company_name, pharmacy_phone, drug_trademark)
VALUES
('54327612', 'Ultram', 'Pfizer'),
('54327612', 'Aleve', 'Abbott'),
('87340213', 'Aleve', 'Abbott'),
('35446281', 'Advil', 'Allergan'),
('98463251', 'Advil', 'Allergan'),
('35446281', 'Irenka', 'Vertex Pharmaceuticals');
```
