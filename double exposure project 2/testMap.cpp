#include "Map.h"
#include <cassert>
#include <iostream>
using namespace std;
int main() {
    //working as of 4:18 pm
    Map mm;
    mm.insert("Little Ricky", 3.206);
    mm.insert("Ethel", 3.538);
    mm.insert("Ricky", 3.350);
    mm.insert("Lucy", 2.956);
    mm.insert("Ethel", 3.538);
    mm.insert("Fred", 2.956);
    mm.insert("Lucy", 2.956);
    assert(mm.size() == 5);  // duplicate "Ethel" and "Lucy" were not added
    string x;
    double y;
    mm.get(0, x, y);
    assert(x == "Ethel");  // "Ethel" is greater than exactly 0 items in mm
    mm.get(4, x, y);
    assert(x == "Ricky");  // "Ricky" is greater than exactly 4 items in mm
    mm.get(2, x, y);
    assert(x == "Little Ricky");  // "Little Ricky" is greater than exactly 2 items in mm
    assert(y == 3.206);  // the value corresponding to the key "Little Ricky"

    //working as of 4:18 pm
    Map m1;
    m1.insert("Fred", 2.956);
    Map m2;
    m2.insert("Ethel", 3.538);
    m2.insert("Lucy", 2.956);
    m1.swap(m2);
    assert(m1.size() == 2 && m1.contains("Ethel") && m1.contains("Lucy") &&
        m2.size() == 1 && m2.contains("Fred"));
    //working as of 4:18 pm
    Map gpas;
    gpas.insert("Fred", 2.956);
    assert(!gpas.contains(""));
    gpas.insert("Ethel", 3.538);
    gpas.insert("", 4.000);
    gpas.insert("Lucy", 2.956);
    assert(gpas.contains(""));
    gpas.erase("Fred");
    assert(gpas.size() == 3 && gpas.contains("Lucy") && gpas.contains("Ethel") &&
        gpas.contains(""));
    string k;
    double v;
    assert(gpas.get(1, k, v) && k == "Ethel");
    assert(gpas.get(0, k, v) && k == "");

    Map kiam;
    assert(!kiam.update("ha", 1));
    //working as of 4:26 pm
    Map names;
    names.insert("bert", 0);
    names.insert("dat", 2);
    names.insert("cat", 1);
    string kar;
    double vue;
    names.get(1, kar, vue);
    assert(kar == "cat");
    names.insert("abacus", 10);
    names.get(0, kar, vue);
    assert(kar == "abacus");
    names.insert("zany", 20);
    names.get(names.size() - 1, kar, vue);
    assert(kar == "zany");

    //working as of 4:27 pm
    Map mek;
    assert(mek.insert("Fred", 2.956));
    assert(mek.insert("Ethel", 3.538));
    assert(mek.size() == 2);
    v = 42;
    assert(!mek.get("Lucy", v) && v == 42);
    assert(mek.get("Fred", v) && v == 2.956);
    v = 42;
    x = "Lucy";
    assert(mek.get(0, x, v) &&
        ((x == "Fred" && v == 2.956) || (x == "Ethel" && v == 3.538)));
    KeyType x2 = "Ricky";
    assert(mek.get(1, x2, v) &&
        ((x2 == "Fred" && v == 2.956) || (x2 == "Ethel" && v == 3.538)) &&
        x != x2);

    //empty map tests
    Map mark;
    assert(mark.empty());
    mark.insert("rumom", 2);
    assert(!mark.update("mak", 7)); // non existent key
    mark.erase("rumom");//verify that erase works
    assert(!mark.contains("rumom")); //does not contain key in empty list
    assert(mark.empty());

    cout << "Passed all tests part 1!!" << endl;
    //copy construction
    Map nk;
    nk.insert("ya", 31);
    nk.insert("fak", 13);
    Map fu(nk);
    assert(fu.contains("ya") && fu.contains("fak"));
    cout << "i worked!" << endl;
    Map o;
    o.insert("yuh", 3.1);
    o.insert("ok", 5.1);
    o.insert("poo", 99.1);
    o.insert("lol", 19);
    Map nic;
    nic.insert("urmom", 10);
    nic = o;
    o.erase("poo");
    assert(nic.contains("yuh") && nic.contains("lol") && nic.contains("poo") && nic.contains("ok"));
    assert(nic.size() == 4);
    nic.erase("lol");
    assert(nic.size() == 3);
    //merge testing
    Map olders;
    olders.insert("Fred", 123);
    olders.insert("Ethel", 456);
    olders.insert("Lucy", 654);
    Map newers;
    newers.insert("Lucy", 789);
    newers.insert("Ricky", 321);
    Map finale;
    assert(!merge(olders, newers, finale));
    assert(finale.contains("Fred") && finale.contains("Ethel") && finale.contains("Ricky") && !finale.contains("Lucy"));

    //reassign testing
    Map mak;
    Map kil;
    KeyType aoi;
    ValueType ako;
    mak.insert("a", 10);
    mak.insert("b", 53);
    mak.insert("c", 30);
    mak.insert("d", 70);
    reassign(mak, kil);
    kil.get(3,aoi, ako);
    assert(ako == 10);

    // default constructor
    Map m;
    // For an empty map:
    assert(m.size() == 0);      // test size
    assert(m.empty());          // test empty
    assert(!m.erase("Ricky"));  // nothing to erase
    assert(!m.update("haha", 20)); // nothing to update
    assert(!m.contains("Ricky")); //empty map contains nothing
    ValueType vorl = 34;
    KeyType korl = "Ricky";
    assert(!m.get(korl, vorl)); //nothing to get
    assert(!m.get(0, korl, vorl)); //nothing to get

    //copy constructor
    Map svap(m);
    assert(svap.empty()); // copied empty map


    svap.insert("yea", 3);
    svap.swap(m);
    assert(svap.empty()); // filled map swaps with empty map and is now empty
    Map ok;
    ok.insert("jump", 99);
    assert(ok.contains("jump")); //test that map contains item
    assert(ok.size() == 1); //test size on non-empty map
    ok.erase("jump"); //test erase
    assert(ok.size() == 0);
    assert(!ok.contains("jump"));
    ok.insert("jake", 30);
    ok.insert("mba", 42);
    ok.insert("msi", 21);
    ok.insert("aba", 32);
    assert(!ok.insert("mba", 21)); // duplicate key, failed insertion
    assert(ok.size() == 4);
    KeyType mh;
    ValueType mal;
    ok.get("aba", mal); // testing get
    assert(mal == 32);
    ok.get(1, mh, mal); //testing get(i) 
    assert(mh == "jake");
    ok.get(2, mh, mal);
    assert(mh == "mba");
    ok.get(3, mh, mal);
    assert(mh == "msi");
    assert(!ok.update("dukck", 900)); // test update on absent key
    assert(ok.insertOrUpdate("dukck", 900)); //test insert or update
    assert(ok.contains("dukck"));
    Map jam;
    Map gem;
    jam.insert("joe", 2);
    jam.insert("kai", 0);
    jam.insert("mick", 19);
    jam.insert("darn", 13);
    gem.insert("june", 91);
    gem.insert("linoleum", 54);
    gem.swap(jam); //testing swap on non-empty arrays
    assert(gem.contains("joe") && gem.contains("kai") && gem.contains("mick") && gem.contains("darn") && gem.size() == 4);
    assert(jam.contains("june") && jam.contains("linoleum") && jam.size() == 2);

    cout << "Passed all tests part 2!" << endl;
}