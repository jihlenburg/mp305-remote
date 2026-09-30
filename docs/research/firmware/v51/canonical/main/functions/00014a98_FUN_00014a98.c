/* Address: 00014a98; name: FUN_00014a98; body bytes: 42 */

void FUN_00014a98(void)

{
  if ((DAT_1fffaae6 != '\0') && (DAT_1fffaadf != '\0')) {
    if (DAT_1ffe016e == '\0') {
      if (DAT_1ffe016f == '\0') {
        return;
      }
      DAT_1ffe016f = '\0';
    }
    else {
      DAT_1ffe016e = '\0';
    }
    FUN_0001cb8c(3);
    return;
  }
  DAT_1ffe016f = 0;
  DAT_1ffe016e = 0;
  return;
}

