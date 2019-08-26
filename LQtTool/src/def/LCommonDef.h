#ifndef LCOMMONDEF
#define LCOMMONDEF

#ifdef Q_OS_WIN
#define NEWLINE "\r\n"
#else
#define NEWLINE "\n"
#endif

#ifdef __arm__
#define TitleMinSize 40
#else
#define TitleMinSize 30
#endif

#endif // LCOMMONDEF

