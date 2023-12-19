#include <iostream>
#include <string>

struct TrafficViolation {
    std::string description;
    TrafficViolation* next;

    TrafficViolation(const std::string& desc) : description(desc), next(nullptr) {}
};

struct CarNode {
    std::string licensePlate;
    TrafficViolation* violations;
    CarNode* left;
    CarNode* right;

    CarNode(const std::string& plate) : licensePlate(plate), violations(nullptr), left(nullptr), right(nullptr) {}
};

class TrafficDatabase {
private:
    CarNode* root;

    CarNode* insertNode(CarNode* node, const std::string& plate) {
        if (node == nullptr) {
            return new CarNode(plate);
        }

        if (plate < node->licensePlate) {
            node->left = insertNode(node->left, plate);
        }
        else if (plate > node->licensePlate) {
            node->right = insertNode(node->right, plate);
        }

        return node;
    }

    void insertViolation(CarNode* node, const std::string& plate, const std::string& violation) {
        if (node->licensePlate == plate) {
            if (node->violations == nullptr) {
                node->violations = new TrafficViolation(violation);
            }
            else {
                TrafficViolation* curr = node->violations;
                while (curr->next != nullptr) {
                    curr = curr->next;
                }
                curr->next = new TrafficViolation(violation);
            }
        }
        else if (plate < node->licensePlate && node->left != nullptr) {
            insertViolation(node->left, plate, violation);
        }
        else if (plate > node->licensePlate && node->right != nullptr) {
            insertViolation(node->right, plate, violation);
        }
    }

    void printDatabase(CarNode* node) {
        if (node != nullptr) {
            printDatabase(node->left);

            std::cout << "��������: " << node->licensePlate << std::endl;

            if (node->violations != nullptr) {
                std::cout << "���������: " << std::endl;
                TrafficViolation* curr = node->violations;
                while (curr != nullptr) {
                    std::cout << curr->description << std::endl;
                    curr = curr->next;
                }
            }
            else {
                std::cout << "��������� �� ����������." << std::endl;
            }

            std::cout << std::endl;

            printDatabase(node->right);
        }
    }

    void printViolations(CarNode* node, const std::string& plate) {
        if (node != nullptr) {
            printViolations(node->left, plate);

            if (node->licensePlate == plate) {
                std::cout << "��������: " << node->licensePlate << std::endl;

                if (node->violations != nullptr) {
                    std::cout << "���������: " << std::endl;
                    TrafficViolation* curr = node->violations;
                    while (curr != nullptr) {
                        std::cout << curr->description << std::endl;
                        curr = curr->next;
                    }
                }
                else {
                    std::cout << "��������� �� ����������." << std::endl;
                }

                std::cout << std::endl;
            }

            printViolations(node->right, plate);
        }
    }

    void printViolationsInRange(CarNode* node, const std::string& startPlate, const std::string& endPlate) {
        if (node != nullptr) {
            if (node->licensePlate >= startPlate && node->licensePlate <= endPlate) {
                std::cout << "��������: " << node->licensePlate << std::endl;

                if (node->violations != nullptr) {
                    std::cout << "���������: " << std::endl;
                    TrafficViolation* curr = node->violations;
                    while (curr != nullptr) {
                        std::cout << curr->description << std::endl;
                        curr = curr->next;
                    }
                }
                else {
                    std::cout << "��������� �� ����������." << std::endl;
                }

                std::cout << std::endl;
            }

            printViolationsInRange(node->left, startPlate, endPlate);
            printViolationsInRange(node->right, startPlate, endPlate);
        }
    }

public:
    TrafficDatabase() : root(nullptr) {}

    void addViolation(const std::string& plate, const std::string& violation) {
        if (root == nullptr) {
            root = new CarNode(plate);
        }

        insertNode(root, plate);
        insertViolation(root, plate, violation);
    }

    void printAll() {
        if (root == nullptr) {
            std::cout << "���� ������ �����." << std::endl;
            return;
        }

        printDatabase(root);
    }

    void printByPlate(const std::string& plate) {
        if (root == nullptr) {
            std::cout << "���� ������ �����." << std::endl;
            return;
        }

        printViolations(root, plate);
    }

    void printInRange(const std::string& startPlate, const std::string& endPlate) {
        if (root == nullptr) {
            std::cout << "���� ������ �����." << std::endl;
            return;
        }

        printViolationsInRange(root, startPlate, endPlate);
    }
};



int main() 
{
    setlocale(LC_ALL, "");
    TrafficDatabase database;

    // ���������� ��������� � ���� ������
    database.addViolation("AB123CD", "���������� ��������");
    database.addViolation("AB123CD", "������� �� ������� ����");
    database.addViolation("XY987ZW", "���������� ��������");
    database.addViolation("XY987ZW", "�������� ��� ����� ������������");
    database.addViolation("PQ456RS", "���������� ��������");

    // ������ ���������� ���� ������
    std::cout << "������ ���� ������:" << std::endl;
    database.printAll();

    // ���������� ��������� �� ��������� ������
    std::cout << "��������� ��� AB123CD:" << std::endl;
    database.printByPlate("AB123CD");

    // ���������� ��������� �� ��������� �������
    std::cout << "��������� � ��������� XY to ZZ:" << std::endl;
    database.printInRange("XY000AA", "ZZ999ZZ");

    return 0;
}