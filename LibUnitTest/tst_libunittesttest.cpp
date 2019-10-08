#include <QString>
#include <QtTest>

class LibUnitTestTest : public QObject
{
    Q_OBJECT

public:
    LibUnitTestTest();

private Q_SLOTS:
    void testCase1();
};

LibUnitTestTest::LibUnitTestTest()
{
}

void LibUnitTestTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(LibUnitTestTest)

#include "tst_libunittesttest.moc"
