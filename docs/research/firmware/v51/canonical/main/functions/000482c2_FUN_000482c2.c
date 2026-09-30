/* Address: 000482c2; name: FUN_000482c2; body bytes: 22 */

undefined4 FUN_000482c2(char *param_1)

{
  if ((param_1 != (char *)0x0) && ((*param_1 == '\x01' || (*param_1 == '\x03')))) {
    return *(undefined4 *)(param_1 + 0x70);
  }
  return 0;
}

