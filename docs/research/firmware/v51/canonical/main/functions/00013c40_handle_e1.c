/* Address: 00013c40; name: handle_e1; body bytes: 62 */

void handle_e1(int param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  if (param_4 == 3) {
    if (DAT_1fff9434 == '\0') {
      DAT_1ffe0184 = 1;
      DAT_1fff9434 = *(undefined1 *)(param_1 + 0x11);
      DAT_1fff9435 = *(undefined1 *)(param_1 + 0x12);
      DAT_1fff9436 = *(undefined1 *)(param_1 + 0x13);
      DAT_1fff9437 = *(undefined1 *)(param_1 + 0x14);
      return;
    }
    DAT_1fff942c = *(undefined1 *)(param_1 + 0x11);
    DAT_1fff942d = *(undefined1 *)(param_1 + 0x12);
    DAT_1fff942e = *(undefined1 *)(param_1 + 0x13);
    DAT_1fff942f = *(undefined1 *)(param_1 + 0x14);
    DAT_1fff9430 = DAT_1fff942c;
    DAT_1fff9431 = DAT_1fff942d;
    DAT_1fff9432 = DAT_1fff942e;
    DAT_1fff9433 = DAT_1fff942f;
  }
  return;
}

