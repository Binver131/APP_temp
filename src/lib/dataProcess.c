char *packData(char *ptr, char *value, int length,char *targetAddress) {
    // 计算数据的长度

    // 将地址存入目标地址
    memcpy(targetAddress, &ptr, sizeof(ptr));
    targetAddress += sizeof(ptr);

    // 将长度存入目标地址
    memcpy(targetAddress, &length, sizeof(length));
    targetAddress += sizeof(length);

    // 将数据存入目标地址
    memcpy(targetAddress, &value, sizeof(value));

    return sizeof(ptr) + sizeof(length) + length + targetAddress;
}
