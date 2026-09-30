/* Address: 0001855c; name: cmd_be; body bytes: 132 */

void cmd_be(int param_1,int param_2)

{
  char cVar1;
  
  cVar1 = *(char *)(param_1 + 1);
  if (cVar1 == '\0') {
    if (DAT_1ffe0192 == '\x01') {
      DAT_1fffaae9 = 1;
    }
    if (DAT_1ffe0193 == '\x01') {
      DAT_1fffaaea = 1;
    }
    DAT_1ffe0193 = 0;
    DAT_1ffe0192 = 0;
    DAT_1ffe0191 = 0;
    cVar1 = *(char *)(param_1 + param_2 + -2);
    if (cVar1 == '\x01') {
      DAT_1ffe01b0 = DAT_1ffe01b0 + 1;
    }
    else {
      if (cVar1 != -1) {
        DAT_1ffe0191 = 0;
        DAT_1ffe0192 = 0;
        DAT_1ffe0193 = 0;
        return;
      }
      DAT_1ffe01b0 = DAT_1ffe01b0 + -1;
    }
    DAT_1ffe016f = 1;
    return;
  }
  if (cVar1 == '\x01') {
    if (DAT_1ffe0192 != '\x02') {
      DAT_1ffe0192 = 1;
      DAT_1ffe0191 = 0;
      DAT_1ffe0193 = 0;
      return;
    }
  }
  else if (cVar1 == '\x02') {
    if (DAT_1ffe0193 != '\x02') {
      DAT_1ffe0191 = 0;
      DAT_1ffe0192 = 0;
      DAT_1ffe0193 = 1;
      return;
    }
  }
  else if ((cVar1 == '\x04') && (DAT_1ffe0191 != '\x02')) {
    DAT_1ffe0191 = 1;
    DAT_1ffe0192 = 0;
    DAT_1ffe0193 = 0;
    return;
  }
  DAT_1ffe0193 = 2;
  DAT_1ffe0192 = 2;
  DAT_1ffe0191 = 2;
  return;
}

