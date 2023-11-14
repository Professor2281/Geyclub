#include <iostream>
#include <vector>
#include <windows.h>

using namespace std;

bool shot = 0, l = 0, r = 0, u = 0, d = 0;
int xl, xr, yu, yd;
int x, y, cnt = 0;

enum ConsoleColor
{
    Black = 0,
    Blue = 1,
    Green = 2,
    Cyan = 3,
    Red = 4,
    Magenta = 5,
    Brown = 6,
    LightGray = 7,
    DarkGray = 8,
    LightBlue = 9,
    LightGreen = 10,
    LightCyan = 11,
    LightRed = 12,
    LightMagenta = 13,
    Yellow = 14,
    White = 15
};

void SetColor(ConsoleColor text, ConsoleColor background)
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

class Table {
public:
    Table(vector <string> l) {
        arr.resize(10, "..........");
        for (int i = 0; i < 10; i++) {
            arr[i] = l[i];
        }
    }
    void addShip(int len)// Добавление корабля рнд
    {
        int ship = 1, xl, yu, xr, yd;
        bool d = 1, u = 1, l = 1, r = 1;
        do {
            y = rand() % 10;
            x = rand() % 10;
        } while (check(y, x));
        xl = x;
        xr = x;
        yu = y;
        yd = y;
        vector<pair<int, int>> filled = { {y, x} };
        while (ship++ < len) {
            vector<pair<int, int>> possible;
            if (l && xl - 1 >= 0 && !check(y, xl - 1)) {
                possible.push_back({ y, xl - 1 });// Лево
            }
            if (r && xr + 1 < 10 && !check(y, xr + 1)) {
                possible.push_back({ y, xr + 1 });// Право
            }
            if (u && yu - 1 >= 0 && !check(yu - 1, x)) {
                possible.push_back({ yu - 1, x });// Вверх
            }
            if (d && yd + 1 < 10 && !check(yd + 1, x)) {
                possible.push_back({ yd + 1, x });// Вниз
            }
            if (possible.size() == 0)
                return addShip(len);
            int rnd = rand() % possible.size();// Рандом
            int yn = possible[rnd].first, xn = possible[rnd].second;
            if (yn == y) {
                u = 0;
                d = 0;
                if (xn == xl - 1)
                    xl--;
                else
                    xr++;
            }
            else {
                l = 0;
                r = 0;
                if (yn == yu - 1)
                    yu--;
                else
                    yd++;
            }
            filled.push_back({ yn, xn });
        }
        if (filled.size() == len) {
            for (auto i : filled) {
                int a = i.first, b = i.second;
                arr[a][b] = 'k';
            }
        }
        else
            addShip(len);
    }
    void fillShips()// Заполнение кораблей
    {
        srand(time(NULL) + cnt++);
        for (int i = 1; i < 5; i++) {
            for (int j = 0; j < 5 - i; j++) {
                addShip(i);
            }
        }
    }
    Table() {
        arr.resize(10, "..........");
        fillShips();
    }
    Table(bool op) {

        arr.resize(10, "..........");
        return;
    }
    string& operator[](int ind) { // обращение к линии по индексу
        return arr[ind];
    }
    /*~Table() {
        delete[] arr;
    }*/
    void print()// Вывод таблицы
    {
        cout << "  ";
        for (int i = 1; i < 11; i++)
            cout << i << " ";
        cout << endl;
        string s = "abcdefghij";
        for (int i = 0; i < 10; i++)
        {
            cout << s[i] << " ";
            for (int a = 0; a < 10; a++)
            {
                switch (arr[i][a]) {
                case 'x':
                    SetColor(Red, Black);
                    break;
                case 'k':
                    SetColor(LightGreen, Black);
                    break;
                default:
                    SetColor(Blue, Black);
                    break;

                }
                cout << arr[i][a] << ' ';

                SetColor(White, Black);
            }
            cout << endl;

        }
        cout << "\n\n";
    }
    void destroyShip(int yu1 = yu, int yd1 = yd, int xl1 = xl, int xr1 = xr)// Уничтожение корабля
    {
        for (int yn = max(yu1 - 1, 0); yn <= min(yd1 + 1, 9); yn++)
        {
            for (int xn = max(xl1 - 1, 0); xn <= min(xr1 + 1, 9); xn++)
            {
                arr[yn][xn] = (arr[yn][xn] == 'x') ? 'x' : 'o';
            }
        }
    }
    bool isShipExist(int x, int y)// Проверка наличия корабля
    {
        int xl = x;
        while (xl > 9 && (arr[y][xl - 1] == 'x' || arr[y][xl - 1] == 'k')) {
            xl--;
            if (arr[y][xl] == 'k')
                return 1;
        }
        int xr = x;
        while (xr < 9 && (arr[y][xr + 1] == 'x' || arr[y][xr + 1] == 'k')) {
            xr++;
            if (arr[y][xr] == 'k')
                return 1;
        }
        int yu = y;
        while (yu > 0 && (arr[yu - 1][x] == 'x' || arr[yu - 1][x] == 'k')) {
            yu--;
            if (arr[yu][x] == 'k')
                return 1;
        }
        int yd = y;
        while (yd < 9 && (arr[yd + 1][x] == 'x' || arr[yd + 1][x] == 'k')) {
            yd++;
            if (arr[yd][x] == 'k')
                return 1;
        }
        return 0;
    }
    bool win() {
        for (int i = 0; i < 10; i++) {

            for (int j = 0; j < 10; j++) {
                if (arr[i][j] == 'k') {
                    return 0;
                }
                if (arr[i][j] == 'k') {
                    return 0;
                }
            }
        }
        return 1;
    }
    int numShit() {
        int cnt = 0;
        for (int i = 0; i < 10; i++) {
            for (int j = 0;j < 10; j++) {
                if (arr[i][j] == 'k') cnt++;

            }
        }
        return cnt;
    }
private:
    vector <string> arr;
    bool check(int y, int x)// Проверка сущуствования кораблей в радиусе 1 клетки 
    {
        for (int i = max(x - 1, 0); i <= min(x + 1, 9); i++) {
            for (int j = max(y - 1, 0); j <= min(y + 1, 9); j++) {
                if (arr[j][i] == 'k')
                    return 1;
            }
        }
        return 0;
    }
};

Table tableplship;
Table tableplshoot(false);
Table tablebotship;
Table tablebotshoot(false);


void aiIfShot(Table& tableBot, Table& tablePl)// Ход ИИ, если тот попал
{
    if ((l || r || d || u) == 0) {
        l = 1;
        r = 1;
        u = 1;
        d = 1;
    }
    vector<pair<int, int>> possible;
    if (l && xl - 1 >= 0 && (tablePl[y][xl - 1] != 'o' || tablePl[y][xl - 1] != 'x'))
        possible.push_back({ y, xl - 1 });// Лево
    if (r && xr + 1 < 10 && (tablePl[y][xr + 1] != 'o' || tablePl[y][xr + 1] != 'x'))
        possible.push_back({ y, xr + 1 });// Право
    if (u && yu - 1 >= 0 && (tablePl[yu - 1][x] != 'o' || tablePl[yu - 1][x] != 'x'))
        possible.push_back({ yu - 1, x });// Вверх
    if (d && yd + 1 < 10 && (tablePl[yd + 1][x] != 'o' || tablePl[yd + 1][x] != 'x'))
        possible.push_back({ yd + 1, x });// Вниз
    if (possible.size() == 0) {
        cout << "ERROR\n";
        return;
    }
    int rnd = rand() % possible.size();
    int yn = possible[rnd].first, xn = possible[rnd].second;
    if (xn > 9 || yn > 9) {
        cout << "UTRF";
        return;
    }
    if (tablePl[yn][xn] == 'k') {
        if (yn == y) {
            u = d = 0;
            if (xn == xl - 1)
                xl--;
            else
                xr++;
        }
        else {
            r = l = 0;
            if (yn == yu - 1)
                yu--;
            else
                yd++;
        }
        tablePl[yn][xn] = 'x';
        tableBot[yn][xn] = 'x';
    }
    else {
        if (xn == xl - 1)
            l = 0;
        else if (xn == xr + 1)
            r = 0;
        else if (yn == yu - 1)
            u = 0;
        else if (yn == yd + 1)
            d = 0;
        tablePl[yn][xn] = 'o';
        tableBot[yn][xn] = 'o';
    }
}

void aiRnd(Table& tableBot, Table& tablePl)// рнд ход бота
{
    vector<pair<int, int>> free;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (tableBot[i][j] == '.') {
                free.push_back({ i, j });
            }
        }
    }
    int rnd = rand() % free.size();// Рандом координаты
    y = free[rnd].first;
    x = free[rnd].second;
    if (tablePl[y][x] == 'k') {
        shot = 1;
        xl = x; xr = x;
        yu = y; yd = y;
    }
    tableBot[y][x] = (tablePl[y][x] == 'k') ? 'x' : 'o';
    tablePl[y][x] = (tablePl[y][x] == 'k') ? 'x' : 'o';
}

void aiHub()// Ход ИИ
{
    if (shot && !(tableplship.isShipExist(x, y))) {
        shot = 0;
        tableplship.destroyShip();
        tablebotshoot.destroyShip();
        l = 0; r = 0; d = 0; u = 0;
    }
    if (shot)
        aiIfShot(tablebotshoot, tableplship);
    else
        aiRnd(tablebotshoot, tableplship);
}

pair <int, int> enter()// Ввод координат
{
    string s;
    char le; int num = 0;
    cout << "Введите через пробел номер строки и ячейки:\n";
    cin >> le >> s;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] >= 48 && s[i] <= 57) {
            num = num * 10 + s[i] - 48;
        }
        else if (s[i] != ' ')// Проверка на корректность ввода
        {
            cout << "Error in input\n";
            return enter();
            break;
        }
        if (num > 10) {
            cout << "Number is too big\n";
            return enter();
        }
    }
    while (le < 97 || le > 107)
    {
        cout << "Буква\"" << le << "\" не доступна, введи букву от a до j" << endl;
        cin >> le;
    }
    int y, x;
    x = num - 1;
    y = le - 97;
    return { y, x };
}

void movePl(Table& tablePlSi, Table& tablePlSo, Table& tableOppSi, int num)// Ход игрока, принимает корабли соперника и свои + свое поле стрельбы для num-го игрока
{
    cout << "ход игрок а №" << num << "\n";
    cout << "ваши корабли\n";
    tablePlSi.print();
    cout << "Поле стрельбы\n";
    tablePlSo.print();
    int y, x;
    pair <int, int> p = enter();
    y = p.first;
    x = p.second;
    if (tableOppSi[y][x] == 'k')//    ранен/убит
    {
        int xl = x, xr = x, yu = y, yd = y;
        tableOppSi[y][x] = 'x';
        tablePlSo[y][x] = 'x';
        bool sh = 0;
        while (xl > 0 && (tableOppSi[y][xl - 1] == 'k' || tableOppSi[y][xl - 1] == 'x'))// X - левая
        {
            xl--;
            if (tableOppSi[y][xl] == 'k')
            {
                sh = 1;
                break;
            }
        }
        while (xr < 9 && (tableOppSi[y][xr + 1] == 'k' || tableOppSi[y][xr + 1] == 'x'))// X - правая
        {
            xr++;
            if (tableOppSi[y][xr] == 'k')
            {
                sh = 1;
                break;
            }
        }
        while (yu > 0 && (tableOppSi[yu - 1][x] == 'k' || tableOppSi[yu - 1][x] == 'x'))// Y - верхняя
        {
            yu--;
            if (tableOppSi[yu][x] == 'k')
            {
                sh = 1;
                break;
            }
        }
        while (yd < 9 && (tableOppSi[yd + 1][x] == 'k' || tableOppSi[yd + 1][x] == 'x'))// Y - нижняя
        {
            yd++;
            if (tableOppSi[yd][x] == 'k')
            {
                sh = 1;
                break;
            }
        }
        if (sh)
        {
            cout << "корабль ранен\n";
        }
        else
        {

            cout << "корабль уничтожен\n";
            printf("%d %d %d %d\n", xl, xr, yu, yd);
            tableOppSi.destroyShip(yu, yd, xl, xr);
            tablePlSo.destroyShip(yu, yd, xl, xr);
        }
        movePl(tablePlSi, tablePlSo, tableOppSi, num);
    }

    else    // Мимо
    {
        tableOppSi[y][x] = 'o';
        tablePlSo[y][x] = 'o';
        cout << "мимо\n";
    }

}

void ClearScreen()
{
    HANDLE                     hStdOut;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD                      count;
    DWORD                      cellCount;
    COORD                      homeCoords = { 0, 0 };

    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdOut == INVALID_HANDLE_VALUE) return;

    /* Get the number of cells in the current buffer */
    if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
    cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    /* Fill the entire buffer with spaces */
    if (!FillConsoleOutputCharacter(
        hStdOut,
        (TCHAR)' ',
        cellCount,
        homeCoords,
        &count
    )) return;

    /* Fill the entire buffer with the current colors and attributes */
    if (!FillConsoleOutputAttribute(
        hStdOut,
        csbi.wAttributes,
        cellCount,
        homeCoords,
        &count
    )) return;

    /* Move the cursor home */
    SetConsoleCursorPosition(hStdOut, homeCoords);
}

void beforeMoves()// Переход хода
{
    cout << "Предыдущий игрок, введите любой символ + enter\n";
    char ch; cin >> ch;
    ClearScreen();
    cout << "Следующий игрок, нажмите любой сивол + enter\n";
    cin >> ch;
    ClearScreen();
}

void game(int num)
{
    if (num == 1) {
        while (!(tableplship.win() || tablebotship.win()))
        {
            movePl(tableplship, tableplshoot, tablebotship, 1);
            if (tablebotship.win())
            {
                cout << "Победа первого игрока\n";
                endGame(tableplship);

                break;
            }
            beforeMoves();
            movePl(tablebotship, tablebotshoot, tableplship, 2);
            if (tableplship.win())
            {
                cout << "Победа второго игрока\n";
                endGame(tablebotship);

                break;
            }
            beforeMoves();
        }
    }
    else {
        while (!(tableplship.win() || tablebotship.win()))
        {
            movePl(tableplship, tableplshoot, tablebotship, 1);
            if (tablebotship.win())
            {
                cout << "Победа первого игрока\n";
                endGame(tableplship);
                break;
            }
            aiHub();
            while (shot)
                aiHub();
            if (tableplship.win())
            {
                cout << "Победа второго игрока\n";
                endGame(tablebotship);
                break;
            }
        }
    }
}

void endGame(Table T) {
    cout << "У игрока осталось " << T.numShit() << " кораблей\n";

}

int main() {
    setlocale(LC_ALL, "Russian");
    cout << "1-PvP\n2-Bot\n";
    int choose;
    cin >> choose;
    while (choose < 1 || choose > 2) {
        cout << "ДЕБИЛ, ОТ 1 ДО 2 ВВОД\n";
        cin >> choose;
    }
    game(choose);
    cout << "Корабли первого игрока\n";
    tableplship.print();
    cout << "Поле стрельбы первого и игрока\n";
    tableplshoot.print();
    cout << "Кораблии второго игрока\n";
    tablebotship.print();
    cout << "Поле стрельбы второго игрока\n";
    tablebotshoot.print();

}
