#include <iostream>
#include <vector>
#include <string>
#include <windows.h> 
#include <ctime> 

using namespace std;

// === ตัวละครวันพีชนะจ้ะอิอิ ===
class Character {
public:
    string name, desc;
    vector<string> artRows; // เก็บรูปแยกบรรทัดเพื่อแสดงผลขนานกัน
    int maxHp, currentHp, atk, def, ultDmg, ultCooldown;

    Character(string n, int a, int d, int h, int u, vector<string> rows, string dsc) {
        name = n; atk = a; def = d; maxHp = h;
        currentHp = h; ultDmg = u; ultCooldown = 0;
        artRows = rows; desc = dsc;
    }

    void takeDamage(int damage) {
        currentHp -= damage;
        if (currentHp < 0) currentHp = 0;
    }
    bool isDead() { return currentHp <= 0; }
    void heal(int amount) {
        currentHp += amount;
        if (currentHp > maxHp) currentHp = maxHp;
    }
    void reduceCooldown() { if (ultCooldown > 0) ultCooldown--; }
};

// === ข้อมูลตัวละคร 8 ตัวหลัก ===
vector<Character> roster = {
    
    Character("ลูฟี่", 22, 14, 100, 45, {"  _👒_  ", " ( o.o) ", " --|--  ", "  / \\   "}, "สมดุล: หมัดปืนกลยางยืด"),
    Character("โซโร", 26, 15, 110, 52, {"  _⚔️_  ", " ( x.x) ", " /| |\\  ", "  / \\   "}, "โจมตีหนัก: เพลงดาบสามดาบ"),
    Character("ซันจิ", 23, 12, 100, 48, {"  _🚬_  ", " ( -.-) ", " --|--  ", "  / \\   "}, "ความเร็ว: ลูกเตะอัคคี"),
    Character("หนวดขาว", 28, 22, 125, 65, {"  _🔱_  ", " < -.- >", " --|--  ", "  / \\   "}, "ถึกทน: พลังสั่นสะเทือน"),
    Character("แชงคูส", 27, 13, 105, 58, {"  _🗡️_  ", " ( ^.^) ", "  /|--  ", "  / \\   "}, "ฮาคิ: ฮาคิราชันย์"),
    Character("เอส", 25, 11, 100, 55, {"  _🔥_  ", " ( *.*) ", "  \\|/   ", "  / \\   "}, "พลังไฟ: หมัดอัคคี"),
    Character("คาตาคุริ", 21, 26, 125, 42, {"  _🧣_  ", " ( #.#) ", "  /|\\   ", "  / \\   "}, "ป้องกันสูง: หมัดโมจิ"),
    Character("ลอว์", 20, 15, 105, 54, {"  _🐯_  ", " ( @.@) ", "  /|\\   ", "  / \\   "}, "เทคนิค: รูม - แชมเบิลส์"),
    Character("นามิ", 18, 10, 85, 70, {"  _☁️_  ", " ( 'o') ", " --|--  ", "  / \\   "}, "เวทย์มนตร์: สายฟ้าฟาด"),
    Character("อุซป", 15, 12, 90, 60, {"  _🎯_  ", " ( >.<) ", " --|--  ", "  / \\   "}, "ระยะไกล: กระสุนดาวกระจาย"),
    Character("โรบิน", 19, 14, 95, 65, {"  _🌸_  ", " ( u.u) ", " /| |\\  ", "  / \\   "}, "ล็อคเป้า: คลัตช์ร้อยบุปผา"),
    Character("ช็อปเปอร์", 12, 18, 120, 50, {"  _🦌_  ", " ( ^.^) ", " --|--  ", "  / \\   "}, "รักษา: รัมเบิลบอล"),
    Character("แฟรงกี้", 24, 25, 130, 40, {"  _🤖_  ", " ( O.O) ", " [| |]  ", "  / \\   "}, "กึ่งหุ่นยนต์: สตรองไรท์"),
    Character("บรู๊ค", 17, 11, 80, 55, {"  _🎻_  ", " ( x.x) ", " --|--  ", "  | |   "}, "รวดเร็ว: เพลงดาบฮัมเพลง"),
    Character("จินเบ", 25, 20, 140, 45, {"  _🌊_  ", " ( v.v) ", " /| |\\  ", "  / \\   "}, "จู่โจมน้ำ: หมัดคาราเต้มนุษย์เงือก"),
    Character("ไคโด", 30, 28, 150, 70, {"  _🐉_  ", " ( @.@) ", " /| |\\  ", "  / \\   "}, "บอส: อัสนีแปดทิศ"),
    Character("บิ๊กมัม", 29, 27, 145, 75, {"  _🍰_  ", " ( >0<) ", " /| |\\  ", "  / \\   "}, "ควบคุมวิญญาณ: มาม่ามาม่า"),
    Character("ทีช (หนวดดำ)", 26, 18, 115, 80, {"  _🌑_  ", " ( `.` )", " --|--  ", "  / \\   "}, "หลุมดำ: คุโรซึ (วังวนมืด)"),
    Character("มิฮอว์ค", 32, 15, 100, 60, {"  _🦅_  ", " ( -.-) ", " --|--  ", "  / \\   "}, "แม่นยำ: คลื่นดาบยักษ์"),
    Character("โดฟลามิงโก้", 23, 17, 105, 65, {"  _🦩220_  ", " ( -.-) ", " /| |\\  ", "  / \\   "}, "ควบคุม: กรงนก")
   
};

// === ระบบวาดหน้าจอต่อสู้ ===
void drawBattle(Character p1, Character p2) {
    system("cls");
    cout << "====================================================" << endl;
    cout << "      PLAYER 1                     PLAYER 2" << endl;
    cout << "      " << p1.name << "                     " << p2.name << endl;
    cout << "----------------------------------------------------" << endl;
    
    for (int i = 0; i < 4; i++) {
        cout << "    " << p1.artRows[i] << "             VS          " << p2.artRows[i] << endl;
    }

    cout << "----------------------------------------------------" << endl;
    cout << "  HP: " << p1.currentHp << "/" << p1.maxHp << "               HP: " << p2.currentHp << "/" << p2.maxHp << endl;
    cout << "  ULT: " << (p1.ultCooldown == 0 ? "READY!" : to_string(p1.ultCooldown)) 
         << "                ULT: " << (p2.ultCooldown == 0 ? "READY!" : to_string(p2.ultCooldown)) << endl;
    cout << "====================================================" << endl;
}

// === ระบบเลือกตัวละคร ===
int selectCharacter(int playerNum, int excludeIdx = -1) {
    int choice;
    char confirm;
    while (true) {
        system("cls");
        cout << "=== ค้นหาเจ้าโจรสลัด (ผู้เล่นคนที่ " << playerNum << ") ===" << endl;
        for (int i = 0; i < (int)roster.size(); i++) {
            if (i == excludeIdx) cout << i + 1 << ". [เลือกแล้ว] " << roster[i].name << endl;
            else cout << i + 1 << ". " << roster[i].name << endl;
        }
        cout << "\nเลือกตัวละคร (1-20): ";
        if (!(cin >> choice)) { cin.clear(); cin.ignore(1000,'\n'); continue; }
        
        int idx = choice - 1;
        if (idx >= 0 && idx < (int)roster.size() && idx != excludeIdx) {
            system("cls");
            cout << "--- รายละเอียดตัวละคร ---\n" << endl;
            for(string s : roster[idx].artRows) cout << s << endl;
            cout << "\nชื่อ: " << roster[idx].name << " | " << roster[idx].desc << endl;
            cout << "HP: " << roster[idx].maxHp << " | ATK: " << roster[idx].atk << " | DEF: " << roster[idx].def << endl;
            cout << "\nยืนยันตัวละครนี้? (y/n): ";
            cin >> confirm;
            if (confirm == 'y' || confirm == 'Y') return idx;
        } else {
            cout << "!! กรุณาเลือกหมายเลขที่ถูกต้อง !!" << endl;
            Sleep(800);
        }
    }
}

// === ระบบคำนวณเทิร์น ===
void playTurn(Character &attacker, Character &defender, int playerNum) {
    int action;
    bool valid = false;

    while (!valid) {
        cout << "\n>> เทิร์นของ " << attacker.name << " (P" << playerNum << ")" << endl;
        cout << "1. โจมตีปกติ | 2. ท่าไม้ตาย | 3. พักฟื้น (+20 HP): ";
        
        // --- ส่วนที่แก้ไข: เช็คว่า Input เป็นตัวเลขหรือไม่ ---
        if (!(cin >> action)) { 
            cout << "!! กรุณากรอกเฉพาะตัวเลข 1, 2 หรือ 3 เท่านั้น !!" << endl;
            cin.clear(); // ล้าง Error State ของ cin
            cin.ignore(1000, '\n'); // ลบข้อมูลขยะที่ค้างอยู่ใน Buffer ทิ้งไป
            continue; // เริ่ม Loop ใหม่ทันที
        }
        // -------------------------------------------

        int dmg = 0;
        int rnd = (rand() % 9) - 4; 

        if (action == 1) {
            dmg = (attacker.atk - (defender.def / 3)) + rnd;
            if (dmg < 8) dmg = 8;
            defender.takeDamage(dmg);
            cout << ">> " << attacker.name << " บุกจู่โจม! สร้างความเสียหาย: " << dmg << endl;
            attacker.reduceCooldown();
            valid = true;
        } 
        else if (action == 2) {
            if (attacker.ultCooldown == 0) {
                dmg = attacker.ultDmg + rnd;
                defender.takeDamage(dmg);
                attacker.ultCooldown = 4;
                cout << ">> " << attacker.name << " ปล่อยท่าไม้ตายสุดยอด!!! สร้างความเสียหาย: " << dmg << endl;
                valid = true;
            } else {
                cout << "!! ท่าไม้ตายยังติดคูลดาวน์ (รออีก " << attacker.ultCooldown << " เทิร์น) !!" << endl;
            }
        } 
        else if (action == 3) {
            attacker.heal(20);
            attacker.reduceCooldown();
            cout << ">> " << attacker.name << " พักฟื้นร่างกาย ฟื้นฟู HP แล้ว!" << endl;
            valid = true;
        } 
        else {
            cout << "!! ไม่มีคำสั่งนี้ โปรดเลือก 1-3 เท่านั้น !!" << endl;
        }
    }Sleep(1500); 
}
    

int main() {
    SetConsoleOutputCP(65001); // แสดงผลภาษาไทยบน Windows
    srand(time(0));

    // เลือกตัวละคร
    int p1Idx = selectCharacter(1);
    Character p1 = roster[p1Idx];

    int p2Idx = selectCharacter(2, p1Idx);
    Character p2 = roster[p2Idx];

    // เริ่มการต่อสู้
    while (!p1.isDead() && !p2.isDead()) {
        drawBattle(p1, p2);
        playTurn(p1, p2, 1);
        if (p2.isDead()) break;

        drawBattle(p1, p2);
        playTurn(p2, p1, 2);
    }

    // จบเกม
    drawBattle(p1, p2);
    if (p1.isDead()) cout << "\n👑 ผู้ชนะคือ: " << p2.name << " (PLAYER 2) 👑" << endl;
    else cout << "\n👑 ผู้ชนะคือ: " << p1.name << " (PLAYER 1) 👑" << endl;

    cout << "\nขอบคุณที่ร่วมศึกชิงเจ้าโจรสลัด!" << endl;
    system("pause");
    return 0;
}