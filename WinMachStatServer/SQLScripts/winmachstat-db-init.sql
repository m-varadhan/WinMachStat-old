CREATE DATABASE winmachstat ;

USE winmachstat;

CREATE TABLE `sysinfo` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `client_key` varchar(32) NOT NULL,
  `memory` int(11) NOT NULL,
  `cpu` int(11) NOT NULL,
  `processes` int(11) NOT NULL,
  `log_date` date DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `sysinfo_idx` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
