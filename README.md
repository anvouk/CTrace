# CTrace

C/C++ logging library.
<br><br>
The library is divided in these 2 parts:

### CTrace
Lightweight cross-platform logging library.

### CWinTrace
Pretty much the same as CTrace but adds the following features:
- Console ouput uses colors.
- Can retrieve windows error messages.
- TCHAR support.

## Usage
### CTrace
```cpp
void important_function(void)
{
  /* these are not necessary but often useful */
  CTRACE_ENTER_FN();
  
  /* ... does stuff ... */
  
  if (/* condition */) {
    /* An has error occured. Log it and return. */
    CTRACEE("oops! %d - %s", some_number, some_string);
    CTRACE_EXIT_FN();
    return;
  }
  
  /* ... more stuff ... */
  
  /* these are not necessary but often useful */
  CTRACE_EXIT_FN();
}
```

### CWinTrace
```cpp
void important_function(void)
{
  /* these are not necessary but often useful */
  CWTRACE_ENTER_FN();
  
  /* ... does stuff ... */
  
  if (/* condition */) {
    /* An has error occured. Log it and return. */
    CWTRACEE(TEXT("oops! %d - %s"), some_number, some_wide_string);
    CWTRACE_EXIT_FN();
    return;
  }
  
  /* ... more stuff ... */
  
  /* these are not necessary but often useful */
  CWTRACE_EXIT_FN();
}
```

## More Examples
See the <a href="https://github.com/QwertyQaz414/CTrace/tree/master/examples">examples folder</a>
