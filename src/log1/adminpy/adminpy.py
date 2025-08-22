import yaml
import sys
def read_yaml(yaml_path, header_path):
    try:
        with open(yaml_path, 'r') as f:
            config = yaml.safe_load(f)
        with open(header_path, 'w') as f:
            f.write("#ifndef ADMIN_H\n")
            f.write("#define ADMIN_H\n\n")

            if 'features' in config:
                for name,enable in config['features'].items():
                    macro_name = f"{name}".replace('-', '_')
                    f.write(f"#define {macro_name} {1 if enable else 0}\n")
            f.write("\n#endif // ADMIN_H\n")

        print("生成成功：{header_path}")
    except Exception as e:
        print(f"生成失败：{e}")
        sys.exit(1)
if __name__ == '__main__':
    if len(sys.argv) < 3:
        print("参数错误，请指定yaml文件路径和头文件路径\n")
        print(f"{sys.argv[0]} <admin.yaml> <admin.h> ",file=sys.stderr)
        sys.exit(1)
    yaml_path = sys.argv[1]
    header_path = sys.argv[2]
    read_yaml(yaml_path, header_path)