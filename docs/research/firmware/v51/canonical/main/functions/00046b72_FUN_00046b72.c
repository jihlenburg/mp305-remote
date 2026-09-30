/* Address: 00046b72; name: FUN_00046b72; body bytes: 100 */

undefined2 FUN_00046b72(int param_1,uint param_2,undefined4 param_3)

{
  undefined1 auStack_20 [4];
  undefined2 local_1c;
  
  if (param_1 != 0) {
    if ((((((param_2 < 0x20) || (param_2 == 0x61c)) || (param_2 == 0x115f)) ||
         ((param_2 == 0x1160 || (param_2 - 0x180b < 4)))) ||
        ((param_2 - 0x200b < 5 || ((param_2 - 0x2028 < 8 || (param_2 - 0x205f < 0x11)))))) ||
       ((param_2 == 0xfeff || (param_2 == 0xf8ff)))) {
      local_1c = 0;
    }
    else {
      FUN_00046a36(param_1,auStack_20,param_2,param_3);
    }
    return local_1c;
  }
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}

