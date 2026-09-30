/* Address: 00011864; name: FUN_00011864; body bytes: 138 */

void FUN_00011864(int param_1)

{
  undefined2 local_30;
  undefined2 local_2e;
  undefined2 local_26;
  
  if (DAT_1ffe018b == '\0') {
    FUN_0001540c(&local_30);
    local_30 = 1;
    local_2e = 2;
    local_26 = 0x40;
    FUN_000152e0(7,2,&local_30);
    FUN_00015384(7,2);
    DAT_1ffe018b = '\x01';
    DAT_1ffe01b4 = 0;
    DAT_1fff9b9a = 0;
    DAT_1fff9b9b = 0;
  }
  else {
    DAT_1ffe01b4 = param_1 + DAT_1ffe01b4;
    if (999 < DAT_1ffe01b4) {
      FUN_000153e0(7,2);
      FUN_0001540c(&local_30);
      local_30 = 1;
      local_2e = 0;
      local_26 = 0x40;
      FUN_000152e0(7,2,&local_30);
      DAT_1ffe018b = '\0';
      DAT_1ffe01b4 = 0;
      DAT_1fff9b91 = 0;
      DAT_1ffe018e = 0;
    }
  }
  return;
}

