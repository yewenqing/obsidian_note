from PIL import Image
from PIL.ExifTags import TAGS

image = Image.open("2A99055CA9FF6A0C59ADC88A87D4D35A.JPG")
exif_data = image._getexif()

if exif_data:
    for tag_id, value in exif_data.items():
        tag_name = TAGS.get(tag_id, tag_id)
        print(f"{tag_name}: {value}")
else:
    print("该图片没有包含任何 EXIF 元数据。")