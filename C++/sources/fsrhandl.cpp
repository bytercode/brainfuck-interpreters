#include "defs.hpp"

fsrhandl::fsrhandl()
{
    this->ttype = 0;
    this->strindx = 0;
    this->buf = nullptr;
}

int fsrhandl::openfile(const char *filename, bool bin)
{
    if (!std::experimental::filesystem::exists(filename)) return -1;
    this->ttype = 1;
    this->fs.open(filename, bin ? std::ios::binary : std::ios::in);
    return !this->fs.bad();
}

void fsrhandl::openstring(const char *str)
{
    this->ttype = 2;
    this->buf = new char[strlen(str)];
    strcpy(this->buf, str);
    return;
}

void fsrhandl::close()
{
    switch (ttype)
    {
    case 1:
        this->fs.close();
        this->fs.clear();
        break;
    case 2:
        delete[] this->buf;
        this->strindx = 0;
        this->buf = nullptr;
        break;
    }
    this->ttype = 0;
}

short fsrhandl::get_type() {return this->ttype;}

short fsrhandl::getach()
{
    if (ttype == 1)
    {
        if (this->fs.eof()) return -1;
        return this->fs.get();
    }
    if (ttype == 2)
    {
        short rslt = this->buf[this->strindx++];
        if (rslt < 1)
        {
            return -1;
        }
        return rslt;
    }
    return -1;
}

void fsrhandl::seek(unsigned long index)
{
    if (ttype == 1) this->fs.seekg(index);
    if (ttype == 2) this->strindx = index;
}

unsigned long fsrhandl::tell()
{
    if (ttype == 1) return this->fs.tellg();
    if (ttype == 2) return this->strindx;
    return 0;
}
