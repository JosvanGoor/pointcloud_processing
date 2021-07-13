#include "utility.ih"

char const *dtype_name(uint8_t type) noexcept
{
    switch (type)
    {
        case 1: return "int8";
        case 2: return "uint8";
        case 3: return "int16";
        case 4: return "uint16";
        case 5: return "int32";
        case 6: return "uint32";
        case 7: return "float32";
        case 8: return "float64";
        default: return "unknown type";
    }
}

ostream &operator<<(ostream &out, sensor_msgs::PointCloud2 const &pc) noexcept
{
    out << "Pointcloud2:\n";
    out << "      height: " << pc.height << "\n";
    out << "       width: " << pc.width << "\n";
    out << "   bigendian: " << (pc.is_bigendian ? "true" : "false") << "\n";
    out << "  point_step: " << pc.point_step << "\n";
    out << "    row_step: " << pc.row_step << "\n";
    out << "    is_dense: " << (pc.is_dense ? "true" : "false") << "\n";
    out << "      fields:\n";
    for (auto const &field : pc.fields)
    {
        out << "        - ";
        out << field.name;
        out << ", " << "offset: " << field.offset;
        out << ", " << "type: " << dtype_name(field.datatype);
        out << ", " << "count: " << field.count;
        out << "\n";
    }
    return out;
}